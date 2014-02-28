#!/usr/bin/env python

from dbrpy import *
from threading import Thread

import base64
import json
import re
import time
import web

SESS = 'TEST'
TMOUT = 2000

class WorkerHandler(Handler):
    def __init__(self, clnt):
        super(WorkerHandler, self).__init__()
        self.clnt = clnt
    def on_async(self, fn):
        return fn(self.clnt)

def worker(ctx):
    pool = Pool(8 * 1024 * 1024)
    clnt = Clnt(ctx, SESS, 'tcp://localhost:3270', 'tcp://localhost:3271',
                millis(), pool)
    handler = WorkerHandler(clnt)
    while not clnt.is_ready():
        clnt.dispatch(TMOUT, handler)
    # Temporary hack for test purposes.
    trec = clnt.find_rec_mnem(ENTITY_TRADER, 'WRAMIREZ')
    clnt.logon(trec, TMOUT)
    while clnt.is_open():
        clnt.dispatch(TMOUT, handler)

class CloseRequest(object):
    def __call__(self, clnt):
        return clnt.close(TMOUT)

class TraderRequest(object):
    @staticmethod
    def toDict(trec):
        return {
            'id': trec.id,
            'mnem': trec.mnem,
            'display': trec.display,
            'email': trec.email
        }
    def __init__(self, mnems):
        self.mnems = set(mnems)
    def __call__(self, clnt):
        traders = []
        if self.mnems:
            for mnem in self.mnems:
                trec = clnt.find_rec_mnem(ENTITY_TRADER, mnem)
                if trec:
                    traders.append(TraderRequest.toDict(trec))
        else:
            traders = [TraderRequest.toDict(trec)
                       for trec in clnt.list_rec(ENTITY_TRADER)]
        return traders

class AccntRequest(object):
    @staticmethod
    def toDict(arec):
        return {
            'id': arec.id,
            'mnem': arec.mnem,
            'display': arec.display,
            'email': arec.email
        }
    def __init__(self, mnems):
        self.mnems = set(mnems)
    def __call__(self, clnt):
        accnts = []
        if self.mnems:
            for mnem in self.mnems:
                arec = clnt.find_rec_mnem(ENTITY_ACCNT, mnem)
                if arec:
                    accnts.append(AccntRequest.toDict(arec))
        else:
            accnts = [AccntRequest.toDict(arec)
                      for arec in clnt.list_rec(ENTITY_ACCNT)]
        return accnts

class ContrRequest(object):
    @staticmethod
    def toDict(crec):
        return {
            'id': crec.id,
            'mnem': crec.mnem,
            'display': crec.display,
            'asset_type': crec.asset_type,
            'asset': crec.asset,
            'ccy': crec.ccy,
            'tick_numer': crec.tick_numer,
            'tick_denom': crec.tick_denom,
            'lot_numer': crec.lot_numer,
            'lot_denom': crec.lot_denom,
            'price_dp': crec.price_dp,
            'pip_dp': crec.pip_dp,
            'qty_dp': crec.qty_dp,
            'min_lots': crec.min_lots,
            'max_lots': crec.max_lots
        }
    def __init__(self, mnems):
        self.mnems = set(mnems)
    def __call__(self, clnt):
        contrs = []
        if self.mnems:
            for mnem in self.mnems:
                crec = clnt.find_rec_mnem(ENTITY_CONTR, mnem)
                if crec:
                    contrs.append(ContrRequest.toDict(crec))
        else:
            contrs = [ContrRequest.toDict(crec)
                      for crec in clnt.list_rec(ENTITY_CONTR)]
        return contrs

class LogonRequest(object):
    def __init__(self, mnem):
        self.mnem = mnem
    def __call__(self, clnt):
        trec = clnt.find_rec_mnem(ENTITY_TRADER, self.mnem)
        return clnt.logon(trec, TMOUT) if trec else -1

class LogoffRequest(object):
    def __init__(self, mnem):
        self.mnem = mnem
    def __call__(self, clnt):
        trec = clnt.find_rec_mnem(ENTITY_TRADER, self.mnem)
        return clnt.logoff(trec, TMOUT) if trec else -1

class OrderRequest(object):
    @staticmethod
    def toDict(order):
        return {
            'id': order.id
        }
    def __init__(self, mnem):
        self.mnem = mnem
    def __call__(self, clnt):
        orders = []
        trec = clnt.find_rec_mnem(ENTITY_TRADER, self.mnem)
        if trec:
            trader = clnt.trader(trec)
            orders = [OrderRequest.toDict(order)
                      for order in trader.list_order()]
        return orders

class ExecRequest(object):
    def __init__(self, mnem):
        self.mnem = mnem
    def __call__(self, clnt):
        return []

class MembRequest(object):
    def __init__(self, mnem):
        self.mnem = mnem
    def __call__(self, clnt):
        return []

class PosnRequest(object):
    def __init__(self, mnem):
        self.mnem = mnem
    def __call__(self, clnt):
        return []

class ViewRequest(object):
    @staticmethod
    def levelDict(level):
        return {
            'ticks': level.ticks,
            'lots': level.lots,
            'count': level.count
        }
    @staticmethod
    def toDict(view):
        return {
            'cid': view.cid,
            'settl_date': view.settl_date,
            'list_bid': [ViewRequest.levelDict(level) for level in view.list_bid],
            'list_ask': [ViewRequest.levelDict(level) for level in view.list_ask]
        }
    def __init__(self, mnems, settl_dates):
        self.mnems = set(mnems)
        self.settl_dates = {int(x) for x in settl_dates}
    def __call__(self, clnt):
        cids = set()
        for mnem in self.mnems:
            crec = clnt.find_rec_mnem(ENTITY_CONTR, mnem)
            if crec:
                cids.add(crec.id)
        views = []
        if cids:
            if self.settl_dates:
                # Cids and settl_dates.
                for cid in cids:
                    for settl_date in self.settl_dates:
                        view = clnt.find_view(crec.id, settl_date)
                        if view:
                            views.append(ViewRequest.toDict(view))
            else:
                # Cids only.
                views = [ViewRequest.toDict(view) for view in clnt.list_view()
                         if view.cid in cids]
        else:
            if self.settl_dates:
                # Settl_dates only.
                views = [ViewRequest.toDict(view) for view in clnt.list_view()
                         if view.settl_date in self.settl_dates]
            else:
                # Neither cids nor settl_dates.
                views = [ViewRequest.toDict(view) for view in clnt.list_view()]
        return views

urls = (
    '/',               'IndexHandler',
    '/api/trader',     'TraderHandler',
    '/api/accnt',      'AccntHandler',
    '/api/contr',      'ContrHandler',
    '/api/order/(.+)', 'OrderHandler',
    '/api/exec/(.+)',  'ExecHandler',
    '/api/memb/(.+)',  'MembHandler',
    '/api/posn/(.+)',  'PosnHandler',
    '/api/view',       'ViewHandler'
)

allowed = (
    ('WRAMIREZ', 'test'),
    ('SFLORES', 'test'),
    ('JWRIGHT', 'test'),
    ('VCAMPBEL', 'test'),
    ('GWILSON', 'test'),
    ('BJONES', 'test'),
    ('TLEE', 'test'),
    ('EEDWARDS', 'test'),
    ('RALEXAND', 'test'),
    ('JTHOMAS', 'test')
)

def auth():
    auth = web.ctx.env.get('HTTP_AUTHORIZATION')
    if auth is not None:
        auth = re.sub('^Basic ', '', auth)
        user, passwd = base64.decodestring(auth).split(':')
        if (user, passwd) in allowed:
            return user
    web.header('WWW-Authenticate', 'Basic realm="Doobry"')
    web.ctx.status = '401 Unauthorized'
    return None

class Index:
    def GET(self):
        return 'Doobry Index Page'

class TraderHandler:
    def GET(self):
        username = auth()
        if username is None:
            return
        async = web.ctx.async
        async.send(TraderRequest(web.input(mnem = []).mnem))
        web.header('Content-Type', 'application/json')
        return json.dumps(async.recv())

class AccntHandler:
    def GET(self):
        username = auth()
        if username is None:
            return
        async = web.ctx.async
        async.send(AccntRequest(web.input(mnem = []).mnem))
        web.header('Content-Type', 'application/json')
        return json.dumps(async.recv())

class ContrHandler:
    def GET(self):
        username = auth()
        if username is None:
            return
        async = web.ctx.async
        async.send(ContrRequest(web.input(mnem = []).mnem))
        web.header('Content-Type', 'application/json')
        return json.dumps(async.recv())

class OrderHandler:
    def GET(self, mnem):
        username = auth()
        if username is None:
            return
        async = web.ctx.async
        async.send(OrderRequest(mnem))
        web.header('Content-Type', 'application/json')
        return json.dumps(async.recv())

class ExecHandler:
    def GET(self, mnem):
        username = auth()
        if username is None:
            return
        async = web.ctx.async
        async.send(ExecRequest(mnem))
        web.header('Content-Type', 'application/json')
        return json.dumps(async.recv())

class MembHandler:
    def GET(self, mnem):
        username = auth()
        if username is None:
            return
        async = web.ctx.async
        async.send(MembRequest(mnem))
        web.header('Content-Type', 'application/json')
        return json.dumps(async.recv())

class PosnHandler:
    def GET(self, mnem):
        username = auth()
        if username is None:
            return
        async = web.ctx.async
        async.send(PosnRequest(mnem))
        web.header('Content-Type', 'application/json')
        return json.dumps(async.recv())

class ViewHandler:
    def GET(self):
        username = auth()
        if username is None:
            return
        async = web.ctx.async
        params = web.input(mnem = [], settl_date = [])
        async.send(ViewRequest(params.mnem, params.settl_date))
        web.header('Content-Type', 'application/json')
        return json.dumps(async.recv())

def run():
    ctx = ZmqCtx()
    thread = Thread(target = worker, args = (ctx,))
    thread.start()
    async = Async(ctx, SESS)
    app = web.application(urls, globals())
    def loadhook():
        web.ctx.async = async
    app.add_processor(web.loadhook(loadhook))
    app.run()
    print('shutdown')
    async.send(CloseRequest())
    async.recv()
    thread.join()

if __name__ == '__main__':
    try:
        run()
    except Error as e:
        print 'error: ' + str(e)

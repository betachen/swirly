# The Restful Matching-Engine.
# Copyright (C) 2013, 2016 Swirly Cloud Limited.
#
# This program is free software; you can redistribute it and/or modify it under the terms of the
# GNU General Public License as published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if
# not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.

from swift import *

class TestCase(RestTestCase):

  def test(self):
    self.maxDiff = None
    self.now = 1388534400000
    with DbFile() as dbFile:
      with Server(dbFile, self.now) as server:
        with Client() as client:
          client.setTime(self.now)

          self.createMarket(client, 'EURUSD', 20140302)
          self.createMarket(client, 'EURUSD', 20140402)
          self.createMarket(client, 'GBPUSD', 20140302)

          self.createOrder(client, 'MARAYL', 'EURUSD', 20140302, 'SELL', 3, 12346)
          self.createOrder(client, 'MARAYL', 'EURUSD', 20140302, 'BUY', 3, 12344)

          self.createOrder(client, 'MARAYL', 'EURUSD', 20140402, 'SELL', 5, 12347)
          self.createOrder(client, 'MARAYL', 'EURUSD', 20140402, 'BUY', 5, 12343)

          self.createOrder(client, 'MARAYL', 'GBPUSD', 20140302, 'SELL', 3, 15346)
          self.createOrder(client, 'MARAYL', 'GBPUSD', 20140302, 'BUY', 3, 15344)

          self.checkAuth(client)

          self.getAll(client)
          self.getByContr(client)
          self.getByMarket(client)
          self.getById(client)

      with Server(dbFile, self.now) as server:
        with Client() as client:
          client.setTime(self.now)

          self.getAll(client)
          self.getByContr(client)
          self.getByMarket(client)
          self.getById(client)

  def checkAuth(self, client):
    client.setAuth(None, 0x2)

    resp = client.send('GET', '/accnt/order')
    self.assertEqual(401, resp.status)
    self.assertEqual('Unauthorized', resp.reason)

    resp = client.send('GET', '/accnt/order/EURUSD')
    self.assertEqual(401, resp.status)
    self.assertEqual('Unauthorized', resp.reason)

    resp = client.send('GET', '/accnt/order/EURUSD/20140302')
    self.assertEqual(401, resp.status)
    self.assertEqual('Unauthorized', resp.reason)

    client.setAuth('MARAYL', ~0x2 & 0x7fffffff)

    resp = client.send('GET', '/accnt/order')
    self.assertEqual(403, resp.status)
    self.assertEqual('Forbidden', resp.reason)

    resp = client.send('GET', '/accnt/order/EURUSD')
    self.assertEqual(403, resp.status)
    self.assertEqual('Forbidden', resp.reason)

    resp = client.send('GET', '/accnt/order/EURUSD/20140302')
    self.assertEqual(403, resp.status)
    self.assertEqual('Forbidden', resp.reason)

  def getAll(self, client):
    client.setTrader('MARAYL')
    resp = client.send('GET', '/accnt/order')

    self.assertEqual(200, resp.status)
    self.assertEqual('OK', resp.reason)
    self.assertListEqual([{
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 1,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 82255,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'SELL',
      u'state': u'NEW',
      u'ticks': 12346
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 2,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 82255,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'BUY',
      u'state': u'NEW',
      u'ticks': 12344
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 1,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 5,
      u'marketId': 82286,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 5,
      u'settlDate': 20140402,
      u'side': u'SELL',
      u'state': u'NEW',
      u'ticks': 12347
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 2,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 5,
      u'marketId': 82286,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 5,
      u'settlDate': 20140402,
      u'side': u'BUY',
      u'state': u'NEW',
      u'ticks': 12343
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'GBPUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 1,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 147791,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'SELL',
      u'state': u'NEW',
      u'ticks': 15346
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'GBPUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 2,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 147791,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'BUY',
      u'state': u'NEW',
      u'ticks': 15344
    }], resp.content)

  def getByContr(self, client):
    client.setTrader('MARAYL')
    resp = client.send('GET', '/accnt/order/EURUSD')

    self.assertEqual(200, resp.status)
    self.assertEqual('OK', resp.reason)
    self.assertListEqual([{
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 1,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 82255,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'SELL',
      u'state': u'NEW',
      u'ticks': 12346
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 2,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 82255,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'BUY',
      u'state': u'NEW',
      u'ticks': 12344
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 1,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 5,
      u'marketId': 82286,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 5,
      u'settlDate': 20140402,
      u'side': u'SELL',
      u'state': u'NEW',
      u'ticks': 12347
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 2,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 5,
      u'marketId': 82286,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 5,
      u'settlDate': 20140402,
      u'side': u'BUY',
      u'state': u'NEW',
      u'ticks': 12343
    }], resp.content)

  def getByMarket(self, client):
    client.setTrader('MARAYL')
    resp = client.send('GET', '/accnt/order/EURUSD/20140302')

    self.assertEqual(200, resp.status)
    self.assertEqual('OK', resp.reason)
    self.assertListEqual([{
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 1,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 82255,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'SELL',
      u'state': u'NEW',
      u'ticks': 12346
    }, {
      u'accnt': u'MARAYL',
      u'contr': u'EURUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 2,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 82255,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'BUY',
      u'state': u'NEW',
      u'ticks': 12344
    }], resp.content)

  def getById(self, client):
    client.setTrader('MARAYL')
    resp = client.send('GET', '/accnt/order/GBPUSD/20140302/1')

    self.assertEqual(200, resp.status)
    self.assertEqual('OK', resp.reason)
    self.assertDictEqual({
      u'accnt': u'MARAYL',
      u'contr': u'GBPUSD',
      u'cost': 0,
      u'created': self.now,
      u'exec': 0,
      u'id': 1,
      u'lastLots': None,
      u'lastTicks': None,
      u'lots': 3,
      u'marketId': 147791,
      u'minLots': None,
      u'modified': self.now,
      u'ref': None,
      u'resd': 3,
      u'settlDate': 20140302,
      u'side': u'SELL',
      u'state': u'NEW',
      u'ticks': 15346
    }, resp.content)

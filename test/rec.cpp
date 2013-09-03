/*
 *  Copyright (C) 2013 Mark Aylett <mark.aylett@gmail.com>
 *
 *  This file is part of Doobry written by Mark Aylett.
 *
 *  Doobry is free software; you can redistribute it and/or modify it under the terms of the GNU
 *  General Public License as published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  Doobry is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 *  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with this program; if
 *  not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301 USA.
 */
#include "journ.hpp"
#include "model.hpp"
#include "test.hpp"

#include <dbrpp/exch.hpp>
#include <dbrpp/pool.hpp>

using namespace dbr;

template <int TypeN>
struct TypeTraits;

template <>
struct TypeTraits<DBR_TRADER> {
    typedef TraderRecRef TypeRecRef;
};

template <>
struct TypeTraits<DBR_ACCNT> {
    typedef AccntRecRef TypeRecRef;
};

template <>
struct TypeTraits<DBR_CONTR> {
    typedef ContrRecRef TypeRecRef;
};

template <int TypeN>
static typename TypeTraits<TypeN>::TypeRecRef
get_rec_id(Exch& exch, DbrIden id)
{
    auto it = exch.recs<TypeN>().find(id);
    check(it != exch.recs<TypeN>().end());
    return typename TypeTraits<TypeN>::TypeRecRef(*it);
}

template <int TypeN>
static typename TypeTraits<TypeN>::TypeRecRef
get_rec_mnem(Exch& exch, const char* mnem)
{
    auto it = exch.recs<TypeN>().find(mnem);
    check(it != exch.recs<TypeN>().end());
    return typename TypeTraits<TypeN>::TypeRecRef(*it);
}

TEST_CASE(find_contr)
{
    Journ journ(1);
    Model model;
    Pool pool;
    Exch exch(&journ, &model, pool);

    check(exch.crecs().find("BAD") == exch.crecs().end());

    ContrRecRef crec = get_rec_mnem<DBR_CONTR>(exch, "EURUSD");
    check(crec == get_rec_id<DBR_CONTR>(exch, crec.id()));
    check(crec.mnem() == Mnem("EURUSD"));

    // Body.
    check(crec.display() == Display("EURUSD"));
    check(crec.asset_type() == Mnem("CURRENCY"));
    check(crec.asset() == Mnem("EUR"));
    check(crec.ccy() == Mnem("USD"));
    check(fequal(crec.price_inc(), 0.0001));
    check(fequal(crec.qty_inc(), 1e6));
    check(crec.price_dp() == 4);
    check(crec.pip_dp() == 4);
    check(crec.qty_dp() == 0);
    check(crec.min_lots() == 1);
    check(crec.max_lots() == 10);
}

TEST_CASE(find_trader)
{
    Journ journ(1);
    Model model;
    Pool pool;
    Exch exch(&journ, &model, pool);

    check(exch.trecs().find("BAD") == exch.trecs().end());

    TraderRecRef trec = get_rec_mnem<DBR_TRADER>(exch, "WRAMIREZ");
    check(trec == get_rec_id<DBR_TRADER>(exch, trec.id()));
    check(trec.mnem() == Mnem("WRAMIREZ"));

    // Body.
    check(trec.display() == Display("Wayne Ramirez"));
    check(trec.email() == Email("wayne.ramirez@doobry.org"));
}

TEST_CASE(find_accnt)
{
    Journ journ(1);
    Model model;
    Pool pool;
    Exch exch(&journ, &model, pool);

    check(exch.arecs().find("BAD") == exch.arecs().end());

    AccntRecRef arec = get_rec_mnem<DBR_ACCNT>(exch, "DBRA");
    check(arec == get_rec_id<DBR_ACCNT>(exch, arec.id()));
    check(arec.mnem() == Mnem("DBRA"));

    // Body.
    check(arec.display() == Display("Account A"));
    check(arec.email() == Email("dbra@doobry.org"));
}

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

#include <dbrpp/ctx.hpp>
#include <dbrpp/pool.hpp>

#include <dbr/conv.h>
#include <dbr/book.h>

using namespace dbr;

TEST_CASE(book_id)
{
    Pool pool;
    Journ journ(1);
    Model model(pool);
    Ctx ctx(pool, &journ, &model);

    ContrRecs::Iterator it = ctx.crecs().find("EURUSD");
    check(it != ctx.crecs().end());

    ContrRecRef crec(*it);
    BookRef book = ctx.book(*it, 20130824);
    check(book.crec() == crec);
    check(book.settl_date() == 20130824);
}
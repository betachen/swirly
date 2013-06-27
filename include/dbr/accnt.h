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
#ifndef DBR_ACCNT_H
#define DBR_ACCNT_H

#if !defined(DBR_HIDE_API)

#include <dbr/defs.h>
#include <dbr/types.h>

/**
 * @addtogroup Accnt
 * @{
 */

// Returns the account-id for state.

DBR_API DbrIden
dbr_accnt_id(DbrAccnt accnt);

/** @} */

/**
 * @addtogroup AccntTrade
 * @{
 */

DBR_API struct DbrRbNode*
dbr_accnt_find_trade_id(DbrAccnt accnt, DbrIden id);

DBR_API struct DbrRbNode*
dbr_accnt_first_trade(DbrAccnt accnt);

DBR_API struct DbrRbNode*
dbr_accnt_last_trade(DbrAccnt accnt);

DBR_API struct DbrRbNode*
dbr_accnt_end_trade(DbrAccnt accnt);

DBR_API DbrBool
dbr_accnt_empty_trade(DbrAccnt accnt);

/** @} */

/**
 * @addtogroup AccntPosn
 * @{
 */

DBR_API struct DbrRbNode*
dbr_accnt_find_posn_id(DbrAccnt accnt, DbrIden id);

DBR_API struct DbrRbNode*
dbr_accnt_first_posn(DbrAccnt accnt);

DBR_API struct DbrRbNode*
dbr_accnt_last_posn(DbrAccnt accnt);

DBR_API struct DbrRbNode*
dbr_accnt_end_posn(DbrAccnt accnt);

DBR_API DbrBool
dbr_accnt_empty_posn(DbrAccnt accnt);

/** @} */

/**
 * @addtogroup AccntSess
 * @{
 */

DBR_API void
dbr_accnt_set_sess(DbrAccnt accnt, DbrAccntSess sess);

DBR_API DbrAccntSess
dbr_accnt_sess(DbrAccnt accnt);

/** @} */

#endif // !defined(DBR_HIDE_API)

#endif // DBR_ACCNT_H
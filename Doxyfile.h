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
/**
 * @mainpage Doobry
 *
 * This project provides the core components for an open-source matching engine.
 *
 * Matching engines are used in financial trading systems to match buyers and sellers in a
 * market-place.
 *
 * Investment banks and other financial organisations often build in-house matching engines to
 * facilitate trading between desks and reduce the cost of trading on external venues.
 *
 * Matching engines tend to follow a pre-defined set of rules and present mostly technical
 * challenges. Open-sourcing the technical parts of a trading platform allows businesses to focus on
 * their IP-sensitive pricing and trading algorithms.
 *
 * The goal of this project is to eventually host an educational trading platform that will allow
 * market-participants to experiment and compete in a risk-free environment.
 *
 * The core libraries are written in C11, which are supplemented with C++11 wrappers for
 * convenience.
 *
 * The matching engine currently favours performance over a rich feature set.
 */

/**
 * @defgroup Ash Ash
 */

/**
 * @defgroup Defs Defs
 * @ingroup Ash
 */

/**
 * @defgroup Cont Container
 * @ingroup Ash
 */

/**
 * @defgroup Node Node
 * @ingroup Cont
 * @example slnode.cpp
 */

/**
 * @defgroup List List
 * @ingroup Cont
 */

/**
 * @defgroup Prioq Prioq
 * @ingroup Cont
 * @example prioq.cpp
 */

/**
 * @defgroup Queue Queue
 * @ingroup Cont
 */

/**
 * @defgroup Stack Stack
 * @ingroup Cont
 */

/**
 * @defgroup Tree Tree
 * @ingroup Cont
 */

/**
 * @defgroup Util Utility
 * @ingroup Ash
 * @example util.cpp
 */

/**
 * @defgroup Err Error
 * @ingroup Util
 * @example err.cpp
 */

/**
 * @defgroup Lexer Lexer
 * @ingroup Util
 */

/**
 * @defgroup Log Log
 * @ingroup Util
 */

/**
 * @defgroup Pack Pack
 * @ingroup Util
 * @example pack.cpp
 */

/**
 * @defgroup String String
 * @ingroup Util
 */

/**
 * @defgroup Elm Elm
 */

/**
 * @defgroup Types Types
 * @ingroup Elm
 */

/**
 * @defgroup TypesRec Record
 * @ingroup Types
 */

/**
 * @defgroup TypesOrder Order
 * @ingroup Types
 */

/**
 * @defgroup TypesLevel Level
 * @ingroup Types
 */

/**
 * @defgroup TypesExec Execution
 * @ingroup Types
 */

/**
 * @defgroup TypesTrans Transaction
 * @ingroup Types
 */

/**
 * @defgroup TypesMemb Member
 * @ingroup Types
 */

/**
 * @defgroup TypesPosn Position
 * @ingroup Types
 */

/**
 * @defgroup TypesView View
 * @ingroup Types
 */

/**
 * @defgroup Conv Conversion
 * @ingroup Elm
 */

/**
 * @defgroup Pool Pool
 * @ingroup Elm
 * @example pool.cpp
 */

/**
 * @defgroup Proto Proto
 * @ingroup Elm
 * @example proto.cpp
 */

/**
 * @defgroup ProtoTrader Trader
 * @ingroup Proto
 */

/**
 * @defgroup ProtoAccnt Account
 * @ingroup Proto
 */

/**
 * @defgroup ProtoContr Contract
 * @ingroup Proto
 */

/**
 * @defgroup ProtoOrder Order
 * @ingroup Proto
 */

/**
 * @defgroup ProtoExec Execution
 * @ingroup Proto
 */

/**
 * @defgroup ProtoMemb Member
 * @ingroup Proto
 */

/**
 * @defgroup ProtoPosn Position
 * @ingroup Proto
 */

/**
 * @defgroup ProtoView View
 * @ingroup Proto
 */

/**
 * @defgroup Msg Msg
 * @ingroup Elm
 */

/**
 * @defgroup Model Model
 * @ingroup Elm
 * @example model.cpp
 */

/**
 * @defgroup Journ Journal
 * @ingroup Elm
 */

/**
 * @defgroup ZmqStore ZmqStore
 * @ingroup Elm
 */

/**
 * @defgroup Fig Fig
 */

/**
 * @defgroup Trader Trader
 * @ingroup Fig
 */

/**
 * @defgroup TraderOrder Order
 * @ingroup Trader
 */

/**
 * @defgroup TraderTrade Trade
 * @ingroup Trader
 */

/**
 * @defgroup TraderMemb Member
 * @ingroup Trader
 */

/**
 * @defgroup Accnt Account
 * @ingroup Fig
 */

/**
 * @defgroup AccntPosn Position
 * @ingroup Accnt
 */

/**
 * @defgroup AccntMemb Member
 * @ingroup Accnt
 */

/**
 * @defgroup Book Book
 * @ingroup Fig
 */

/**
 * @defgroup Side Side
 * @ingroup Book
 * @example side.cpp
 */

/**
 * @defgroup SideOrder Order
 * @ingroup Side
 */

/**
 * @defgroup SideLevel Level
 * @ingroup Side
 */

/**
 * @defgroup SideLast Last
 * @ingroup Side
 */

/**
 * @defgroup Clnt Client
 * @ingroup Fig
 */

/**
 * @defgroup ClntRecData RecData
 * @ingroup Clnt
 */

/**
 * @defgroup ClntExec Execution
 * @ingroup Clnt
 */

/**
 * @defgroup ClntMktData MktData
 * @ingroup Clnt
 */

/**
 * @defgroup Serv Server
 * @ingroup Fig
 * @example serv.cpp
 */

/**
 * @defgroup ServRecData RecData
 * @ingroup Serv
 */

/**
 * @defgroup ServExec Execution
 * @ingroup Serv
 */

/**
 * @defgroup ServMktData MktData
 * @ingroup Serv
 */

/**
 * @defgroup Text Text
 * @ingroup Fig
 */

/**
 * @defgroup Fir Fir
 */

/**
 * @defgroup SqlStore SqlStore
 * @ingroup Fir
 */

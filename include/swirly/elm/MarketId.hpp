/*
 * The Restful Matching-Engine.
 * Copyright (C) 2013, 2016 Swirly Cloud Limited.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#ifndef SWIRLY_ELM_MARKETID_HPP
#define SWIRLY_ELM_MARKETID_HPP

#include <swirly/ash/BasicTypes.hpp>
#include <swirly/ash/Date.hpp>

namespace swirly {

constexpr Id64 toMarketId(Id32 contrId, JDay settlDay) noexcept
{
  return Id64{(contrId.count() << 16) | (jdToTjd(settlDay) & 0xffff)};
}

constexpr Id64 toMarketId(Id32 contrId, IsoDate settlDate) noexcept
{
  return toMarketId(contrId, maybeIsoToJd(settlDate));
}

template <typename ValueT>
struct MarketIdTraits {
  using Id = Id64;
  static Id id(const ValueT& value) noexcept { return value.marketId(); }
};

} // swirly

#endif // SWIRLY_ELM_MARKETID_HPP

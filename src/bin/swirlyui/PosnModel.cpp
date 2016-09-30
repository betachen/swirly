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
#include "PosnModel.hpp"

#include <algorithm>

using namespace std;

namespace swirly {
namespace ui {
using namespace posn;

PosnModel::PosnModel(QObject* parent) : QAbstractTableModel{parent}
{
  header_[column::MarketId] = tr("Market Id");
  header_[column::Contr] = tr("Contr");
  header_[column::SettlDate] = tr("Settl Date");
  header_[column::Accnt] = tr("Accnt");
  header_[column::BuyLots] = tr("Buy Lots");
  header_[column::BuyAvgPrice] = tr("Buy Avg Price");
  header_[column::SellLots] = tr("Sell Lots");
  header_[column::SellAvgPrice] = tr("Sell Avg Price");
}

PosnModel::~PosnModel() noexcept = default;

int PosnModel::rowCount(const QModelIndex& parent) const
{
  return rows_.size();
}

int PosnModel::columnCount(const QModelIndex& parent) const
{
  return column::Count;
}

QVariant PosnModel::data(const QModelIndex& index, int role) const
{
  QVariant var{};
  if (!index.isValid()) {
    // No-op.
  } else if (role == Qt::DisplayRole) {
    const auto& posn = rows_.nth(index.row())->second;
    switch (index.column()) {
    case column::MarketId:
      var = posn.marketId();
      break;
    case column::Contr:
      var = posn.contr().mnem();
      break;
    case column::SettlDate:
      var = posn.settlDate();
      break;
    case column::Accnt:
      var = posn.accnt();
      break;
    case column::BuyLots:
      var = posn.buyLots();
      break;
    case column::BuyAvgPrice:
      var = ticksToAvgPriceString(posn.buyLots(), posn.buyCost(), posn.contr());
      break;
    case column::SellLots:
      var = posn.sellLots();
      break;
    case column::SellAvgPrice:
      var = ticksToAvgPriceString(posn.sellLots(), posn.sellCost(), posn.contr());
      break;
    }
  } else if (role == Qt::TextAlignmentRole) {
    switch (index.column()) {
    case column::Contr:
    case column::Accnt:
      var = QVariant{Qt::AlignLeft | Qt::AlignVCenter};
      break;
    case column::MarketId:
    case column::SettlDate:
    case column::BuyLots:
    case column::BuyAvgPrice:
    case column::SellLots:
    case column::SellAvgPrice:
      var = QVariant{Qt::AlignRight | Qt::AlignVCenter};
      break;
    }
  } else if (role == Qt::UserRole) {
    var = QVariant::fromValue(rows_.nth(index.row())->second);
  }
  return var;
}

QVariant PosnModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
    return QVariant{};
  }
  return header_[section];
}

void PosnModel::updateRow(const Posn& posn)
{
  auto it = rows_.lower_bound(posn.marketId());
  const int i = distance(rows_.begin(), it);

  const bool found{it != rows_.end() && !rows_.key_comp()(posn.marketId(), it->first)};
  if (found) {
    it->second = posn;
    emit dataChanged(index(i, 0), index(i, column::Count - 1));
  } else {
    // If not found then insert.
    beginInsertRows(QModelIndex{}, i, i);
    rows_.emplace_hint(it, posn.marketId(), posn);
    endInsertRows();
  }
}

} // ui
} // swirly
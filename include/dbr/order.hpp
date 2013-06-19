#ifndef DBR_ORDER_HPP
#define DBR_ORDER_HPP

#include <dbr/rec.hpp>

namespace dbr {

class Order {
    const DbrOrder& impl_;
public:
    explicit
    Order(const DbrOrder& impl) noexcept
        : impl_(impl)
    {
    }
    bool
    operator ==(Order rhs) const noexcept
    {
        return impl_.id == rhs.impl_.id;
    }
    bool
    operator !=(Order rhs) const noexcept
    {
        return impl_.id != rhs.impl_.id;
    }
    DbrIden
    id() const noexcept
    {
        return impl_.id;
    }
    int
    rev() const noexcept
    {
        return impl_.rev;
    }
    int
    status() const noexcept
    {
        return impl_.status;
    }
    TraderRec
    trec() const noexcept
    {
        return TraderRec(*impl_.trader.rec);
    }
    AccntRec
    arec() const noexcept
    {
        return AccntRec(*impl_.accnt.rec);
    }
    Ref
    ref() const noexcept
    {
        return Ref(impl_.ref);
    }
    MarketRec
    mrec() const noexcept
    {
        return MarketRec(*impl_.market.rec);
    }
    int
    action() const noexcept
    {
        return impl_.action;
    }
    DbrTicks
    ticks() const noexcept
    {
        return impl_.ticks;
    }
    DbrLots
    resd() const noexcept
    {
        return impl_.resd;
    }
    DbrLots
    exec() const noexcept
    {
        return impl_.exec;
    }
    DbrLots
    lots() const noexcept
    {
        return impl_.lots;
    }
    DbrLots
    min() const noexcept
    {
        return impl_.min;
    }
    DbrFlags
    flags() const noexcept
    {
        return impl_.flags;
    }
    DbrMillis
    created() const noexcept
    {
        return impl_.created;
    }
    DbrMillis
    modified() const noexcept
    {
        return impl_.modified;
    }
    bool
    done() const noexcept
    {
        return impl_.resd == 0;
    }
};

inline std::ostream&
operator <<(std::ostream& os, Order order)
{
    return os << "id=" << order.id()
              << ",rev=" << order.rev()
              << ",status=" << order.status()
              << ",trec=" << order.trec().mnem()
              << ",arec=" << order.arec().mnem()
              << ",ref=" << order.ref()
              << ",mrec=" << order.mrec().mnem()
              << ",action=" << order.action()
              << ",ticks=" << order.ticks()
              << ",resd=" << order.resd()
              << ",exec=" << order.exec()
              << ",lots=" << order.lots()
              << ",min=" << order.min()
              << ",flags=" << order.flags()
              << ",created=" << order.created()
              << ",modified=" << order.modified();
}
} // dbr

#endif // DBR_ORDER_HPP

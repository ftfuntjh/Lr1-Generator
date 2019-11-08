//
// Created by ftfunjth on 2019/11/8.
//

#include "HandlerSet.h"

#include <utility>

using std::set;
using std::move;
using std::equal;

HandlerSet::HandlerSet(Item item) : shift{move(item)}, handlerList{} {

}

HandlerSet::HandlerSet(Item item, set<Handler> handlers) : shift{move(item)}, handlerList{move(handlers)} {

}

const Item &HandlerSet::shiftItem() {
    return shift;
}

set<Handler> &HandlerSet::ruleList() {
    return handlerList;
}

bool HandlerSet::operator<(const HandlerSet &other) const {
    if (shift < other.shift || other.shift < shift) {
        return shift < other.shift;
    } else {
        return equal(handlerList.begin(), handlerList.end(), other.handlerList.begin());
    }
}

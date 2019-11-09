//
// Created by ftfunjth on 2019/11/8.
//

#include "HandlerSet.h"

#include <utility>

using std::set;
using std::move;
using std::equal;
using std::lexicographical_compare;

HandlerSet::HandlerSet(Item item) : shift{move(item)}, handlerList{}, id{} {

}

HandlerSet::HandlerSet(Item item, set<Handler> handlers) : shift{move(item)}, handlerList{move(handlers)}, id{} {

}

const Item &HandlerSet::shiftItem() {
    return shift;
}

set<Handler> &HandlerSet::ruleList() {
    return handlerList;
}

bool HandlerSet::operator<(const HandlerSet &other) const {
    auto comp = [](const Handler &a1, const Handler &a2) { return a1 < a2; };
    return lexicographical_compare(handlerList.begin(), handlerList.end(), other.handlerList.begin(),
                                   other.handlerList.end(), comp);

}

bool HandlerSet::operator==(const HandlerSet &other) const {
    if (handlerList.size() != other.handlerList.size()) {
        return false;
    }
    return shift == other.shift && equal(handlerList.begin(), handlerList.end(), other.handlerList.begin());
}

void HandlerSet::setId(int pid) {
    this->id = pid;
}

void HandlerSet::setParentId(int parentId) {
    this->parent = parentId;
}

int HandlerSet::getId() {
    return id;
}

int HandlerSet::getParentId() {
    return parent;
}

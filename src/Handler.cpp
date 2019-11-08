//
// Created by 曹高阳 on 2019-11-08.
//

#include "Handler.h"
#include <utility>

using std::optional;
using std::move;
using std::vector;
using std::next;
using std::exception;
using std::set;

Handler::Handler(Production p, size_t pos) : production{move(p)}, position{pos},
                                             lookForward{Item{"$", ItemType::Terminal}} {

}

Handler::Handler(Production p, size_t pos, std::set<Item> const &lookTable) : production{move(p)}, position{pos},
                                                                              lookForward{lookTable.begin(),
                                                                                          lookTable.end()} {

}

vector<Item> Handler::alpha() {
    if (isEnd()) {
        return vector<Item>{};
    }
    return vector<Item>{production.handleList.begin(), B()};
}

auto Handler::B() -> decltype(production.handleList.begin()) {
    return ::next(production.handleList.begin(), position);
}

optional<Item> Handler::bet() {
    if (isEnd()) {
        return optional<Item>{};
    }
    return optional<Item>{production.handleList[position]};
}

bool Handler::isEnd() {
    return position == production.size() - 1;
}

Handler Handler::nextHandler() {
    if (isEnd()) {
        throw std::runtime_error("at production end without nextHandler");
    }
    return Handler{production, position++};
}

set<Item> Handler::getLookForward() {
    return lookForward;
}

Item Handler::current() {

}

void Handler::addLookForward(std::set<Item>::const_iterator begin, std::set<Item>::const_iterator end) {
    lookForward.insert(begin, end);
}

Item Handler::getItem() {
    return production.getItem();
}

bool Handler::operator<(const Handler &handler) const {
    return production.getName() < handler.production.getName();
}

bool Handler::operator==(const Handler &handler) const{
    return production == handler.production && position == handler.position;
}





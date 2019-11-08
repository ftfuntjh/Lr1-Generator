//
// Created by 曹高阳 on 2019-11-08.
//

#include "Handler.h"
#include <iostream>
#include <utility>

using std::optional;
using std::move;
using std::vector;
using std::next;
using std::exception;
using std::set;
using std::cout;
using std::endl;
using std::distance;
using std::equal;
using std::lexicographical_compare;

Handler::Handler(Production p, size_t pos) : production{move(p)}, position{pos},
                                             lookForward{Item{"$", ItemType::Terminal}} {

}

Handler::Handler(Production p, size_t pos, std::set<Item> const &lookTable) :
        production{move(p)},
        position{pos},
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
    return production[position];
}

void Handler::addLookForward(std::set<Item>::const_iterator begin, std::set<Item>::const_iterator end) {
    lookForward.insert(begin, end);
}

Item Handler::getItem() {
    return production.getItem();
}

bool Handler::operator<(const Handler &handler) const {
    if (production.getName() != handler.production.getName()) {
        return production.getName() < handler.production.getName();
    } else {
        auto comparator = [](const Item &a1, const Item &a2) { return a1 < a2; };
        return lexicographical_compare(production.handleList.begin(), production.handleList.end(),
                                       handler.production.handleList.begin(), handler.production.handleList.end(),
                                       comparator);
    }
}

bool Handler::operator==(const Handler &handler) const {
    auto match = equal(production.handleList.begin(), production.handleList.begin(),
                       handler.production.handleList.end());
    return match && production == handler.production && handler.position == position;
}

void Handler::printHandler() {
    cout << production.getName() << " -> ";
    for (int i = 0; i < production.handleList.size(); i++) {
        auto &t = production.handleList[i];
        if (position == i) {
            cout << "·";
        }
        cout << t.getName();
    }
    cout << ",< ";
    for (auto &i : lookForward) {
        cout << i.getName() << " ";
    }
    cout << ">" << endl;
}




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
using std::runtime_error;

Handler::Handler(Production p, size_t pos) : production{move(p)}, position{pos},
                                             lookForward{} {

}

Handler::Handler(Production p, size_t pos, std::set<Item> lookTable) :
        production{move(p)},
        position{pos},
        lookForward(std::move(lookTable)) {

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
    if (position >= production.size() - 1) {
        return optional<Item>{};
    }
    return optional<Item>{production.handleList[position + 1]};
}

optional<vector<Item>> Handler::left() {
    if (position >= production.size() - 1) {
        return optional<vector<Item>>{};
    }
    auto start = production.handleList.begin();
    std::advance(start, position);
    return optional<vector<Item>>{vector<Item>{start, production.handleList.end()}};
}

bool Handler::isEnd() {
    return position >= production.size();
}

Handler Handler::nextHandler() {
    if (isEnd()) {
        throw std::runtime_error("at production end without nextHandler");
    }
    return Handler{production, position + 1, lookForward};
}

set<Item> &Handler::getLookForward() {
    return lookForward;
}

Item Handler::current() {
    if (position > production.size() - 1) {
        throw runtime_error("invalid index");
    }
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
        auto result = lexicographical_compare(production.handleList.begin(), production.handleList.end(),
                                              handler.production.handleList.begin(),
                                              handler.production.handleList.end(),
                                              comparator);
        if (result != 0) {
            return result;
        }
        return position < handler.position;
    }
}

bool Handler::operator==(const Handler &handler) const {
    auto match = equal(production.handleList.begin(), production.handleList.begin(),
                       handler.production.handleList.begin());
    auto lookMatch = equal(lookForward.begin(), lookForward.end(), handler.lookForward.begin());
    return match && lookMatch && production == handler.production && handler.position == position;
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
    if (position == production.handleList.size()) {
        cout << "·";
    }
    cout << ",< ";
    for (auto &i : lookForward) {
        cout << i.getName() << " ";
    }
    cout << ">" << endl;
}




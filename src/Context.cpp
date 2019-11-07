#include "Context.h"
#include <algorithm>
#include <iostream>
#include <utility>

static const Item EMPTY{"^", ItemType::Terminal};
using std::vector;
using std::set;
using std::string;
using std::pair;
using std::cout;
using std::endl;
using std::move;

Context::Context(vector<Production> grammar) : ruleList(move(grammar)), firstSet{}, followSet{} {

}

void Context::first() {
    bool hasChanged;
    do {
        hasChanged = false;
        for (auto &p : ruleList) {
            set<Item> result{};
            size_t j = 0;
            auto pFHasExist = firstExist(p.getName());
            for (; j < p.size(); ++j) {
                bool nullable = false;
                if (p[j].isTerminal()) {
                    result.emplace(p[j]);
                    break;
                }
                auto ntFirstTable = firstAt(p[j]);
                if (ntFirstTable != firstSet.end()) {
                    for (const auto &r : ntFirstTable->second) {
                        if (r.getName() == "^") {
                            nullable = true;
                            continue;
                        }
                        result.emplace(r);
                    }
                }
                if (!nullable) {
                    break;
                }
            }
            if (result.empty()) {
                continue;
            }
            auto production = p.last();
            if (j == p.size() - 1 && production.isNoTerminal() && pFHasExist) {
                auto pTable = firstSet.find(production.getName());
                if (pTable != firstSet.end() &&
                    pTable->second.find(EMPTY) != pTable->second.end()) {
                    result.emplace(EMPTY);
                }
            }
            auto s = firstSet.find(p.getName());
            if (s == firstSet.end()) {
                hasChanged = true;
                firstSet.insert(pair<string, set<Item>>(p.getName(), result));
            } else {
                auto &itemSet = s->second;
                for (auto &item : result) {
                    if (itemSet.find(item) == itemSet.end()) {
                        hasChanged = true;
                        itemSet.emplace(item);
                    }
                }
            }
        }
    } while (hasChanged);
}

void Context::follow() {

}

bool Context::isNullable(const Production &rule) {
    return false;
}

void Context::printFirst() {
    for (auto &pair : firstSet) {
        cout << pair.first << " -> {";
        for (auto p = pair.second.begin(), n = pair.second.end(); p != pair.second.end(); p++) {
            cout << '\'' << p->getName() << '\'';
            n = p;
            n++;
            if (n != pair.second.end()) {
                cout << " ,";
            } else {
                cout << "}" << endl;
            }
        }
    }
}

auto Context::firstAt(const Item &item) -> decltype(firstSet.begin()) {
    return firstSet.find(item.getName());
}

auto Context::firstAt(const string &name) -> decltype(firstSet.begin()) {
    return firstSet.find(name);
}

bool Context::firstExist(const Item &item) {
    return firstAt(item) != firstSet.end();
}

bool Context::firstExist(const std::string &name) {
    return firstAt(name) != firstSet.end();
}



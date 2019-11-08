#include "Context.h"
#include <algorithm>
#include <iostream>
#include <utility>


static const Item EMPTY{"^", ItemType::Terminal};
static const Item Eof{"$", ItemType::Terminal};
using std::vector;
using std::set;
using std::string;
using std::pair;
using std::cout;
using std::endl;
using std::move;
using std::copy_if;
using std::back_inserter;
using std::begin;
using std::end;
using std::runtime_error;

Context::Context(vector<Production> grammar, Production startProduction) : ruleList(move(grammar)), firstSet{},
                                                                           followSet{},
                                                                           start(move(startProduction)) {

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
    const auto startItem = start.getItem();
    followSet.emplace(pair<string, set<Item>>(startItem.getName(), set<Item>{Eof}));

    bool hasChanged;
    do {
        hasChanged = false;
        for (auto &p : ruleList) {
            set<Item> result{};
            if (followSet.find(p.getName()) != followSet.end()) {
                result = followSet.find(p.getName())->second;
            }
            for (int j = p.size() - 1; j >= 0; j--) {
                auto &item = p[j];
                if (item.isNoTerminal()) {
                    if (followSet.find(item.getName()) == followSet.end()) {
                        followSet.insert(pair<string, set<Item>>(item.getName(), result));
                    } else {
                        auto &follow = followSet.find(item.getName())->second;
                        for (auto &i : result) {
                            if (follow.find(i) == follow.end()) {
                                hasChanged = true;
                                follow.emplace(i);
                            }
                        }
                    }
                    auto &firstTable = firstSet.find(item.getName())->second;
                    if (firstTable.find(EMPTY) != firstTable.end()) {
                        result.insert(firstTable.begin(), firstTable.end());
                        result.erase(EMPTY);
                    } else {
                        result = firstTable;
                    }
                } else {
                    if (item == EMPTY) {
                        continue;
                    }
                    result = set<Item>{item};
                }
            }
        }
    } while (hasChanged);
}

bool Context::isNullable(const Item &item) {
    auto iterator = firstSet.find(item.getName());
    if (iterator == end(firstSet)) {
        return false;
    } else {
        return iterator->second.find(EMPTY) != iterator->second.end();
    }
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

void Context::printGrammar() {
    for (auto p : ruleList) {
        cout << p.getItem().getName() << " -> ";
        for (int i = 0; i < static_cast<int>(p.size()); i++) {
            cout << p[i].getName();
        }
        cout << endl;
    }
}

void Context::printFollow() {
    for (auto &pair : followSet) {
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

auto Context::followAt(const Item &item) -> decltype(followSet.begin()) {
    return followSet.find(item.getName());
}

auto Context::followAt(const string &name) -> decltype(followSet.begin()) {
    return followSet.find(name);
}

void Context::generalLr1() {
    bool hasChanged;
    set<HandlerSet> stateSet{};
    auto startHandler = Handler{start, 0, set<Item>{Eof}};
    stateSet.emplace(HandlerSet{Eof, closureSet(startHandler)});
    do {
        hasChanged = false;
        for (auto p : stateSet) {
            auto nextStat = Goto(p);
            if (!nextStat.empty()) {
                hasChanged = true;
                stateSet.insert(nextStat.begin(), nextStat.end());
            }
        }
    } while (hasChanged);
}

set<HandlerSet> Context::Goto(HandlerSet currState) {
    set<HandlerSet> result{};
    set<Item> nTList{};
    set<Item> tList{};
    for (auto h : currState.ruleList()) {
        if (h.isEnd()) {
            continue;
        }
        auto item = h.current();
        if (item.isNoTerminal()) {
            nTList.emplace(item);
        } else if (item.isTerminal() && item.getName() != "^") {
            tList.emplace(item);
        }
    }

    for (auto &nT : nTList) {
        set<Handler> next{};
        for (auto h:currState.ruleList()) {
            if (h.current() == nT && !h.isEnd()) {
                next.emplace(move(h.nextHandler()));
            }
        }
        next = closureItemSet(next);
        result.emplace(HandlerSet{nT, next});
    }
    for (auto &t : tList) {
        set<Handler> next{};
        for (auto h:currState.ruleList()) {
            if (h.current() == t && !h.isEnd()) {
                next.emplace(move(h.nextHandler()));
            }
        }
        next = closureItemSet(next);
        result.emplace(HandlerSet{t, next});
    }
    return result;
}

set<Handler> Context::closureItemSet(set<Handler> &handlerSet) {
    set<Handler> result{};
    for (auto handler : handlerSet) {
        auto closure = closureSet(handler);
        result.insert(closure.begin(), closure.end());
    }
    return result;
}

set<Handler> Context::closureSet(Handler &startHandler) {
    bool hasChanged;
    if (startHandler.getLookForward().empty()) {
        throw runtime_error("invalid start handler");
    }
    set<Handler> result{startHandler};
    do {
        hasChanged = false;
        for (auto currentHandler:result) {
            if (currentHandler.isEnd()) {
                continue;
            }
            auto item = currentHandler.current();
            auto bet = currentHandler.bet();
            if (item.isNoTerminal()) {
                auto pRules = rules(item);
                for (auto &p : pRules) {
                    Handler handler{p, 0};
                    if (!bet) {
                        handler.addLookForward(currentHandler.getLookForward().begin(),
                                               currentHandler.getLookForward().end());
                    } else {
                        auto &val = bet.value();
                        if (val.isNoTerminal() && isNullable(val)) {
                            set<Item> lookItems{currentHandler.getLookForward().begin(),
                                                currentHandler.getLookForward().end()};
                            lookItems.insert(begin(firstAt(val)->second), end(firstAt(val)->second));
                            lookItems.erase(EMPTY);
                            handler.addLookForward(lookItems.begin(), lookItems.end());
                        } else if (val.isTerminal()) {
                            handler.getLookForward().emplace(val);
                        } else {
                            handler.addLookForward(begin(firstAt(val)->second), end(firstAt(val)->second));
                        }
                    }
                    if (result.find(handler) == result.end()) {
                        hasChanged = true;
                        result.emplace(handler);
                    }
                }
            }
        }
    } while (hasChanged);
    return result;
}

std::vector<Production> Context::rules(const Item &item) {
    vector<Production> result{};
    copy_if(ruleList.begin(), ruleList.end(), back_inserter(result), [&item](Production other) {
        return other.getName() == item.getName() && other.getItem().isTerminal() == item.isTerminal();
    });
    return result;
}


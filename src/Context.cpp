#include "Context.h"
#include <algorithm>
#include <iostream>

using std::vector;
using std::set;

Context::Context(const vector<Production> &gammar) : ruleList(gammar), firstSet{}, followSet{} {

}

void Context::first() {
    bool hasChanged;
    do {
        hasChanged = false;
        for (auto &p : ruleList) {
            set<Item> result{};
            size_t j = 0;
            auto firstP = firstSet.find(p.getName());
            for (; j < p.size(); ++j) {
                bool nullable = false;
                if (p[j].isTerminal()) {
                    result.emplace(p[j]);
                    break;
                }
                auto theNt = firstSet.find(p[j].getName());
                if (theNt != firstSet.end()) {
                    for (const auto &r : theNt->second) {
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
            if (j == p.size() - 1 && p[p.size() - 1].isNoTerminal() && firstP != firstSet.end()) {
                auto last = firstSet.find(p[p.size() - 1].getName());
                if (last != firstSet.end() && last->second.find(Item{"^", ItemType::Terminal}) != last->second.end()) {
                    result.emplace(Item{"^", ItemType::Terminal});
                }
            }
            auto s = firstSet.find(p.getName());
            if (s == firstSet.end()) {
                hasChanged = true;
                firstSet.insert(std::pair<std::string, std::set<Item>>(p.getName(), result));
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
        std::cout << pair.first << " -> {";
        for (auto p = pair.second.begin(), n = pair.second.end(); p != pair.second.end(); p++) {
            std::cout << '\'' << p->getName() << '\'';
            n = p;
            n++;
            if (n != pair.second.end()) {
                std::cout << " ,";
            } else {
                std::cout << "}" << std::endl;
            }
        }
    }
}



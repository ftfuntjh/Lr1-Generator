#ifndef CONTEXT_H
#define CONTEXT_H

#include "Common.h"
#include "Production.h"

class Context {
public:
    explicit Context(const std::vector<Production> &grammar);

    void first();

    void follow();

    bool isNullable(const Production &rule);

    void printFirst();

private:
    std::vector<Production> ruleList;
    std::map<std::string, std::set<Item>> firstSet;
    std::map<std::string, std::set<Item>> followSet;
};

#endif

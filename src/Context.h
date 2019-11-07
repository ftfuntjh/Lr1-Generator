#ifndef CONTEXT_H
#define CONTEXT_H

#include "Common.h"
#include "Production.h"

class Context {


public:
    explicit Context(std::vector<Production> grammar);

    void first();


    void follow();

    bool isNullable(const Production &rule);

    void printFirst();

private:
    std::vector<Production> ruleList;
    std::map<std::string, std::set<Item>> firstSet;
    std::map<std::string, std::set<Item>> followSet;

private:
    auto firstAt(const Item &item) -> decltype(firstSet.begin());

    auto firstAt(const std::string &name) -> decltype(firstSet.begin());

    bool firstExist(const Item &item);

    bool firstExist(const std::string &name);
};

#endif

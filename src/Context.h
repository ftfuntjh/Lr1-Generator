#ifndef CONTEXT_H
#define CONTEXT_H

#include "Common.h"
#include "Production.h"
#include "Handler.h"

class Context {
private:
    Production start;
    std::vector<Production> ruleList;
    std::map<std::string, std::set<Item>> firstSet;
    std::map<std::string, std::set<Item>> followSet;
public:
    explicit Context(std::vector<Production> grammar, Production startProduction);

    void first();

    void follow();

    bool isNullable(const Item &item);

    void printFirst();

    void printFollow();

    void printGrammar();

    void generalLr1();

    auto firstAt(const Item &item) -> decltype(firstSet.begin());

    auto firstAt(const std::string &name) -> decltype(firstSet.begin());

    auto followAt(const Item &item) -> decltype(followSet.begin());

    auto followAt(const std::string &name) -> decltype(followSet.begin());

    std::set<Handler> closureSet(Handler &startHandler);

    std::set<Handler> closureItemSet(std::set<Handler> &handlerSet);

    std::set<std::set<Handler>> Goto(std::set<Handler> currState);

private:

    std::vector<Production> rules(const Item &item);


    bool firstExist(const Item &item);

    bool firstExist(const std::string &name);
};

#endif

#ifndef CONTEXT_H
#define CONTEXT_H

#include "Common.h"
#include "Production.h"
#include "Handler.h"
#include "HandlerSet.h"
#include <array>
#include <memory>

class Context {
private:

    Production start;
    std::vector<Production> ruleList;
    std::map<std::string, std::set<Item>> firstSet;
    std::map<std::string, std::set<Item>> followSet;
public:
    using ActionTable = std::vector<std::map<std::string, std::array<int, 2>>>;
    using GotoTable = std::vector<std::map<std::string, int>>;

    explicit Context(std::vector<Production> grammar, Production startProduction);

    void first();

    void follow();

    bool isNullable(const Item &item);

    void printFirst();

    void printFollow();

    void printGrammar();

    std::vector<HandlerSet> generalLr1();

    std::pair<ActionTable, GotoTable> table(std::vector<HandlerSet> &statSet);

    auto firstAt(const Item &item)

    -> decltype(firstSet.begin());

    auto firstAt(const std::string &name) -> decltype(firstSet.begin());

    auto followAt(const Item &item) -> decltype(followSet.begin());

    auto followAt(const std::string &name) -> decltype(followSet.begin());

    std::vector<Handler> closureSet(Handler &startHandler, std::vector<Handler> &result);

    std::vector<Handler> closureItemSet(std::vector<Handler> &handlerSet);

    std::vector<HandlerSet> Goto(HandlerSet currencyHandler);

    void printTable(std::pair<ActionTable, GotoTable> table);

private:

    std::vector<Production> rules(const Item &item);


    bool firstExist(const Item &item);

    bool firstExist(const std::string &name);
};

#endif

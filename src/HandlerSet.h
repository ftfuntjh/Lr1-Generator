//
// Created by ftfunjth on 2019/11/8.
//

#ifndef LR1_HANDLERSET_H
#define LR1_HANDLERSET_H

#include "Handler.h"
#include "Common.h"

class HandlerSet {
public:
    explicit HandlerSet(Item item);

    HandlerSet(Item item, std::set<Handler> handlerList);

    const Item &shiftItem();

    std::set<Handler> &ruleList();

    bool operator<(const HandlerSet &other) const;

private:
    Item shift;
    std::set<Handler> handlerList;
};


#endif //LR1_HANDLERSET_H

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

    HandlerSet(Item item, std::vector<Handler> handlerList);

    const Item &shiftItem();

    std::vector<Handler> &ruleList();

    bool operator<(const HandlerSet &other) const;

    bool operator==(const HandlerSet &other) const;

    void setId(int pid);

    void setParentId(int parentId);

    int getId();

    int getParentId();

private:
    Item shift;
    std::vector<Handler> handlerList;
    int id = -1;
    int parent = -1;
};


#endif //LR1_HANDLERSET_H

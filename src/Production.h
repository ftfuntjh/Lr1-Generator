#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "Item.h"
#include <string>
#include <vector>
#include <algorithm>

class Handler;

class Production {
public:
    friend class Handler;

    Production(const Item &name, const std::vector<Item> &handleList);

    bool operator==(const Production &other) const;

    const Item &operator[](size_t index);

    std::string getName() const {
        return name.getName();
    }

    Item getItem();

    size_t size();

    Item first();

    Item last();

    bool isNullable() const {
        return std::find(handleList.begin(), handleList.end(), Item{"^", ItemType::Terminal}) != handleList.end();
    }

private:
    Item name;
    std::vector<Item> handleList;
};

#endif

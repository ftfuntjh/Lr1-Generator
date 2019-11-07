#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "Item.h"
#include <string>
#include <vector>
#include <algorithm>

class Production {
public:
    Production(const Item &name, const std::vector<Item> &handleList);

    bool operator==(const Production &other);

    const Item &operator[](size_t index);

    std::string getName() const {
        return name.getName();
    }

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

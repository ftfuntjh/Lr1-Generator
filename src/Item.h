#ifndef ITEM_H
#define ITEM_H

#include<string>

enum class ItemType {
    NoTerminal = 0,
    Terminal = 1,
};

class Item {
public:
    Item(std::string itemName, ItemType itemType);

    bool operator==(const Item &other) const;

    bool isNoTerminal() const;

    bool isTerminal() const;

    bool operator<(const Item &other) const;

    std::string getName() const {
        return name;
    }

private:
    std::string name;
    ItemType type;
};

#endif

#include "Item.h"

using std::string;

Item::Item(string itemName, ItemType itemType)
        : name{std::move(itemName)},
          type{itemType} {

}


bool Item::isTerminal() const {
    return this->type == ItemType::Terminal;
}

bool Item::isNoTerminal() const {
    return !isTerminal();
}

bool Item::operator<(const Item &other) const {
    return name < other.name;
}

bool Item::operator==(const Item &other) const {
    return this->type == other.type && this->name == other.name;
}

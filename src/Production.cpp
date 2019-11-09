#include <utility>

#include "Production.h"

Production::Production(Item productionName, const std::vector<Item> &items) :
        name{std::move(productionName)},
        handleList{items.begin(), items.end()} {
}

const Item &Production::operator[](size_t index) {
    return handleList.at(index);
}

bool Production::operator==(const Production &other) const {
    return this->name == other.name;
}

Item Production::first() {
    return this->operator[](0);
}

size_t Production::size() {
    return handleList.size();
}

Item Production::last() {
    return handleList.back();
}

Item Production::getItem() {
    return name;
}

std::vector<Item>::iterator Production::begin() {
    return handleList.begin();
}

std::vector<Item>::iterator Production::end() {
    return handleList.end();
}

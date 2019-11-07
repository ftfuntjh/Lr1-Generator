#include "Production.h"

Production::Production(const Item &productionName, const std::vector<Item> &items) :
        name{productionName},
        handleList{items.begin(), items.end()} {
}

const Item &Production::operator[](size_t index) {
    return handleList.at(index);
}

bool Production::operator==(const Production &other) {
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

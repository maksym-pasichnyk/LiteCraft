#pragma once

#include <set>
//#include <string>

template <typename T>
struct NamedTag {
//    std::string name;
    std::set<T> items;

    template <typename... Args>
    NamedTag& add(Args&&... args) {
        (items.emplace(std::forward<Args>(args)), ...);
        return *this;
    }

    NamedTag& addItemEntry(T item) {
        items.emplace(std::move(item));
        return *this;
    }

    NamedTag& addTag(const NamedTag& tag) {
        items.insert(tag.items.begin(), tag.items.end());
        return *this;
    }

    bool contains(const T& item) const {
        return items.contains(item);
    }
};
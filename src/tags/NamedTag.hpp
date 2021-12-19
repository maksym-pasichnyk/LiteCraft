#pragma once

#include <set>
//#include <string>

template <typename T>
struct NamedTag {
//    std::string name;
    std::set<T> items;

    template <typename... Args>
    auto add(Args&&... args) -> NamedTag& {
        (items.emplace(std::forward<Args>(args)), ...);
        return *this;
    }

    auto addItemEntry(T item) -> NamedTag& {
        items.emplace(std::move(item));
        return *this;
    }

    auto addTag(const NamedTag& tag) -> NamedTag& {
        items.insert(tag.items.begin(), tag.items.end());
        return *this;
    }

    auto contains(const T& item) const -> bool {
        return items.contains(item);
    }
};
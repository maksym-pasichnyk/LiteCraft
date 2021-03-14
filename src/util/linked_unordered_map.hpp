#pragma once

#include <list>
#include <unordered_map>

template <typename K, typename V>
class linked_unordered_map {
    using key_type = typename std::unordered_map<K, V>::key_type;
    std::unordered_map<K, V> hash;
    std::list<K> ls;

public:
    size_t size() const noexcept { return ls.size(); }
    bool empty() const noexcept { return ls.empty(); }

    void insert(std::pair<K, V> kv) {
        const auto p = hash.find(kv.first);
        if (p != hash.end()) {
            p->second = std::move(kv.second);
        } else {
            ls.emplace_back(kv.first);
            hash.emplace(std::move(kv));
        }
    }

    void pop_front() {
        hash.erase(ls.front());
        ls.pop_front();
    }

    bool contains(const K& k) const noexcept {
        return hash.contains(k);
    }

    V& at(const K& k) noexcept {
        return hash.at(k);
    }

    const V& at(const K& k) const noexcept {
        return hash.at(k);
    }
};
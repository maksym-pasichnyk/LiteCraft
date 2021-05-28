#pragma once

#include "Random.hpp"

#include <cmath>
#include <tuple>
#include <vector>
#include <utility>

template <typename T>
struct WeightedList {
    std::vector<std::pair<T, int>> elements;

    template <typename U>
    WeightedList& add(U&& element, int weight) & {
        elements.emplace_back(std::forward<U>(element), weight);
        return *this;
    }

    template <typename U>
    WeightedList&& add(U&& element, int weight) && {
        elements.emplace_back(std::forward<U>(element), weight);
        return std::move(*this);
    }

    decltype(auto) get(Random& random) const {
        size_t index = 0;
        double chance = std::numeric_limits<double>::min();
        for (size_t i = 0; i < elements.size(); i++) {
            const float entry_chance = -std::pow(random.nextFloat(), 1.0f / static_cast<float>(elements[i].second));
            if (chance < entry_chance) {
                chance = entry_chance;
                index = i;
            }
        }
        return elements[index].first;
    }
};
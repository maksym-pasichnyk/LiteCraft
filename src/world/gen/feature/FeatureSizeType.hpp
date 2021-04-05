#pragma once

#include <optional>

#include "TwoLayerFeature.hpp"
#include "ThreeLayerFeature.hpp"

#include <variant>
#include <functional>

struct FeatureSizeType : std::variant<TwoLayerFeature, ThreeLayerFeature> {
    using variant::variant;

    std::optional<int> min_clipped_height() const {
        return std::visit([](auto& self) -> decltype(auto) { return self.min_clipped_height; }, static_cast<const variant&>(*this));
    }

    int func_230369_a_(int min, int max) const {
        return std::visit([min, max](auto& self) -> decltype(auto) { return self.func_230369_a_(min, max); }, static_cast<const variant&>(*this));
    }
};


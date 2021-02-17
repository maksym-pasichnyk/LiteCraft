#pragma once

#include "IAreaTransformer1.hpp"
#include "IDimOffset0Transformer.hpp"
#include "src/world/gen/INoiseRandom.hpp"
#include "src/world/gen/area/IArea.hpp"

template <typename T>
concept cIC0Transformer = requires(T self, IExtendedNoiseRandom& rand, int i) {
    {self.apply(rand, i)} -> std::same_as<int>;
};

template <typename T>
struct IC0Transformer : IDimOffset0Transformer {
    int apply2(IExtendedNoiseRandom& rand, const IArea& area, int x, int z) requires cIC0Transformer<T> {
        const auto d0 = area.getValue(getOffsetX(x), getOffsetZ(z));
        const auto out = static_cast<T*>(this)->apply(rand, d0);
//        std::printf("IC0Transformer[%s]: %d -> %d\n", typeid(T).name(), out, d0);
        return out;
    }
};
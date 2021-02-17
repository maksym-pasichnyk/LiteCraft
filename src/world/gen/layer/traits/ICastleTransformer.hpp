#pragma once

#include "IAreaTransformer1.hpp"
#include "IDimOffset1Transformer.hpp"
#include "src/world/gen/IExtendedNoiseRandom.hpp"
#include "src/world/gen/area/IArea.hpp"

template <typename T>
concept cICastleTransformer = requires(T self, INoiseRandom& rand, int north, int west, int south, int east, int center) {
    { self.apply(rand, north, west, south, east, center)} -> std::same_as<int>;
};

template <typename T>
struct ICastleTransformer : IDimOffset1Transformer {
    int apply2(IExtendedNoiseRandom& rand, const IArea& area, int x, int z) requires cICastleTransformer<T>
    {
        return static_cast<T*>(this)->apply(rand,
                            area.getValue(getOffsetX(x + 1), getOffsetZ(z + 0)),
                            area.getValue(getOffsetX(x + 2), getOffsetZ(z + 1)),
                            area.getValue(getOffsetX(x + 1), getOffsetZ(z + 2)),
                            area.getValue(getOffsetX(x + 0), getOffsetZ(z + 1)),
                            area.getValue(getOffsetX(x + 1), getOffsetZ(z + 1))
        );
    }
};
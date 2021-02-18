#pragma once

#include "IAreaTransformer1.hpp"
#include "src/world/gen/IExtendedNoiseRandom.hpp"
#include "IDimOffset1Transformer.hpp"
#include "src/world/gen/area/IArea.hpp"

template <typename T>
struct IBishopTransformer : IDimOffset1Transformer {
    int apply2(IExtendedNoiseRandom& rand, const IArea auto& area, int x, int z) {
        const auto d0 = area.getValue(getOffsetX(x), getOffsetZ(z + 2));
        const auto d1 = area.getValue(getOffsetX(x + 2), getOffsetZ(z + 2));
        const auto d2 = area.getValue(getOffsetX(x + 2), getOffsetZ(z));
        const auto d3 = area.getValue(getOffsetX(x), getOffsetZ(z));
        const auto d4 = area.getValue(getOffsetX(x + 1), getOffsetZ(z + 1));
        const auto out = static_cast<T *>(this)->apply(rand, d0, d1, d2, d3, d4);
//        std::printf("IBishopTransformer[%s]: %d -> %d, %d, %d, %d, %d\n", typeid(T).name(), out, d0, d1, d2, d3, d4);
        return out;
    }
};
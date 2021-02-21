#pragma once

#include "IAreaTransformer1.hpp"
#include "IDimOffset1Transformer.hpp"
#include "../../IExtendedNoiseRandom.hpp"
#include "../../area/IArea.hpp"

template <typename T>
struct IC1Transformer : IDimOffset1Transformer {
    int apply2(IExtendedNoiseRandom& rand, const IArea auto& area, int x, int z) {
        const auto d0 = area.getValue(getOffsetX(x + 1), getOffsetZ(z + 1));
        const auto out = static_cast<T *>(this)->apply(rand, d0);
//        std::printf("IC1Transformer[%s]: %d -> %d\n", typeid(T).name(), out, d0);
        return out;
    }
};
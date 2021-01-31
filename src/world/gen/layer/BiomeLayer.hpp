#pragma once

#include "src/world/gen/layer/traits/IC0Transformer.hpp"
#include "LayerUtil.hpp"

#include <span>
#include <cassert>

struct BiomeLayer : IC0Transformer<BiomeLayer> {
    static constexpr std::array<int, 6> biomes1{2, 4, 3, 6, 1, 5};
    static constexpr std::array<int, 6> biomes2{2, 2, 2, 35, 35, 1};
    static constexpr std::array<int, 6> biomes3{4, 29, 3, 1, 27, 6};
    static constexpr std::array<int, 4> biomes4{4, 3, 5, 1};
    static constexpr std::array<int, 4> biomes5{12, 12, 12, 30};

    std::array<int, 6> warmBiomes;

public:
    explicit BiomeLayer(bool warm) {
        warmBiomes = warm ? biomes1 : biomes2;
    }

    int apply(INoiseRandom& context, int value) {
        const int i = (value & 3840) >> 8;
        value = value & -3841;

        if (!LayerUtil::isOcean(value) && value != 14) {
            switch(value) {
                case 1:
                    if (i > 0) {
                        return context.random(3) == 0 ? 39 : 38;
                    }

                    return warmBiomes[context.random(std::size(warmBiomes))];
                case 2:
                    if (i > 0) {
                        return 21;
                    }

                    return biomes3[context.random(std::size(biomes3))];
                case 3:
                    if (i > 0) {
                        return 32;
                    }

                    return biomes4[context.random(std::size(biomes4))];
                case 4:
                    return biomes5[context.random(std::size(biomes5))];
                default:
                    return 14;
            }
        }
        return value;
    }
};
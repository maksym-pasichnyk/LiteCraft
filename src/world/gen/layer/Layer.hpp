#pragma once

#include "src/world/gen/layer/area/IArea.hpp"

class Layer {
    IArea area;

public:
    Layer(IArea&& area) : area(std::move(area)) {}

    [[gnu::pure]]
    int getBiomeId(int x, int z) const {
        return area.getValue(x, z);
    }

//    Biome& getBiome(std::map<int, Biome*> biomes, int x, int z) {
//        const auto biomeId = area.getValue(x, z);
//        return *biomes.at(biomeId);
//    }
};
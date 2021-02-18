#pragma once

#include "src/world/gen/area/IArea.hpp"

#include <memory>

class Layer {
    LazyArea area;

public:
    Layer(LazyArea&& area) : area(std::move(area)) {}

    [[gnu::pure]]
    int getBiomeId(int x, int z) const {
        return area.getValue(x, z);
    }

    Biome* getBiome(std::map<int, std::unique_ptr<Biome>>& biomes, int x, int z) {
        const auto biomeId = area.getValue(x, z);
        return biomes.at(biomeId).get();
    }
};
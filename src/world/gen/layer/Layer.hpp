#pragma once

#include "../area/IArea.hpp"

#include <memory>
#include <util/Registry.hpp>

class Layer {
    LazyArea area;

public:
    Layer(LazyArea&& area) : area(std::move(area)) {}

    auto getBiome(const Registry<Biome>& biomes, int x, int z) -> Biome* {
        const auto id = area.getValue(x, z);
        return biomes.entries.at(id).get();
    }
};
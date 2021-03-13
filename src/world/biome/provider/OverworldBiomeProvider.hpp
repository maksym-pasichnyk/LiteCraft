#pragma once

#include "BiomeProvider.hpp"
#include "../../gen/layer/Layer.hpp"

#include <memory>

struct OverworldBiomeProvider : BiomeProvider {
    std::unique_ptr<Layer> genBiomes{};

    OverworldBiomeProvider(int64_t seed, bool legacyBiomes, bool largeBiomes);

    Biome* getNoiseBiome(int x, int y, int z) override;
};
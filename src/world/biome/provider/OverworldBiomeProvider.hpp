#pragma once

#include "BiomeProvider.hpp"
#include "ThreadLocal.hpp"
#include "../../gen/layer/Layer.hpp"

#include <memory>

struct OverworldBiomeProvider : BiomeProvider {
    ThreadLocal<Layer> genBiomes{};

    int64_t seed;
    bool legacyBiomes;
    bool largeBiomes;

    OverworldBiomeProvider(int64_t seed, bool legacyBiomes, bool largeBiomes);

    Biome* getNoiseBiome(int x, int y, int z) override;
};
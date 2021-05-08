#pragma once

#include "BiomeProvider.hpp"
#include "../../gen/layer/Layer.hpp"

#include <memory>

#include <mutex>

struct OverworldBiomeProvider : BiomeProvider {
    std::mutex mutex;
    std::unique_ptr<Layer> genBiomes{};

    OverworldBiomeProvider(int64_t seed, bool legacyBiomes, bool largeBiomes);

    Biome* getNoiseBiome(int x, int y, int z) override;
};
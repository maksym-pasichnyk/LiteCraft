#include "OverworldBiomeProvider.hpp"
#include "../../gen/layer/LayerUtil.hpp"

OverworldBiomeProvider::OverworldBiomeProvider(int64_t seed, bool legacyBiomes, bool largeBiomes) {
    genBiomes = LayerUtil::createOverworldBiomes(seed, legacyBiomes, largeBiomes ? 6 : 4, 4);
}

Biome *OverworldBiomeProvider::getNoiseBiome(int x, int y, int z) {
    return genBiomes->getBiome(Biome::biomes, x, z);
}

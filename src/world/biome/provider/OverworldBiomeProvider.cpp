#include "OverworldBiomeProvider.hpp"
#include "../../gen/layer/LayerUtil.hpp"
#include "../Biomes.hpp"

OverworldBiomeProvider::OverworldBiomeProvider(int64_t seed, bool legacyBiomes, bool largeBiomes) {
    genBiomes = LayerUtil::createOverworldBiomes(seed, legacyBiomes, largeBiomes ? 6 : 4, 4);
}

Biome *OverworldBiomeProvider::getNoiseBiome(int x, int y, int z) {
//    std::lock_guard _{mutex};
    return genBiomes->getBiome(Biomes::biomes, x, z);
}

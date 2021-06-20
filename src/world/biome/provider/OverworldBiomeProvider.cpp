#include "OverworldBiomeProvider.hpp"
#include "../../gen/layer/LayerUtil.hpp"
#include "../Biomes.hpp"

OverworldBiomeProvider::OverworldBiomeProvider(int64_t seed, bool legacyBiomes, bool largeBiomes)
    : seed(seed), legacyBiomes(legacyBiomes), largeBiomes(largeBiomes) {
}

Biome *OverworldBiomeProvider::getNoiseBiome(int x, int y, int z) {
    if (!genBiomes.has_value()) {
        genBiomes.set(LayerUtil::createOverworldBiomes(seed, legacyBiomes, largeBiomes ? 6 : 4, 4).release());
    }
    return genBiomes.get()->getBiome(Biomes::biomes, x, z);
}

#include "DefaultBiomeMagnifier.hpp"
#include "BiomeReader.hpp"

Biome *DefaultBiomeMagnifier::getBiome(int64_t seed, int x, int y, int z, BiomeReader &biomeReader) {
    return biomeReader.getNoiseBiome(x >> 2, y >> 2, z >> 2);
}

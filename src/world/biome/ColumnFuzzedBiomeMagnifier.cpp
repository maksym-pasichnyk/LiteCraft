#include "ColumnFuzzedBiomeMagnifier.hpp"
#include "FuzzedBiomeMagnifier.hpp"

Biome *ColumnFuzzedBiomeMagnifier::getBiome(int64_t seed, int x, int y, int z, BiomeReader &biomeReader) {
    return FuzzedBiomeMagnifier::getBiome(seed, x, 0, z, biomeReader);
}

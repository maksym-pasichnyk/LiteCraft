#include "ConfiguredCarver.hpp"
#include "WorldCarver.hpp"
#include "../../../util/Random.hpp"

bool ConfiguredCarver::shouldCarve(Random &rand, int32_t x, int32_t z) {
    return rand.nextFloat() <= config.probability;
}

bool ConfiguredCarver::carveRegion(Chunk &chunk, const BiomeReadFn &getBiome, Random &rand, int32_t seaLevel, int32_t xoffset, int32_t zoffset, int32_t chunkx, int32_t chunkz) {
    return carver->carveRegion(chunk, getBiome, rand, seaLevel, xoffset, zoffset, chunkx, chunkz/*, carvingMask*/);
}

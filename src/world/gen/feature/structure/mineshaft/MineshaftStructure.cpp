#include "MineshaftStructure.hpp"
#include "MineshaftStart.hpp"
#include "MineshaftRoom.hpp"

bool MineshaftStructure::canGenerate(ChunkGenerator &generator, BiomeProvider &biomes, int64_t seed, Random &random, int x, int z, Biome &biome, const ChunkPos &pos, const StructureConfig &config) {
    random.setLargeFeatureSeed(seed, x, z);
    return random.nextDouble() < std::get<MineshaftConfig>(config).probability;
}

StructureStart *MineshaftStructure::createStart(int x, int z, const BoundingBox &bounds, int refCount, int64_t seed) {
    return new Start(this, x, z, bounds, refCount, seed);
}
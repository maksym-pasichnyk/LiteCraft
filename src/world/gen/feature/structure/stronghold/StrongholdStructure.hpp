//#pragma once
//
//#include <world/gen/feature/structure/Structure.hpp>
//
//struct StrongholdStructure : CfgStructure<> {
//    struct Start;
//
//    bool canGenerate(ChunkGenerator& generator, BiomeProvider& biomes, int64_t seed, Random& random, int x, int z, Biome& biome, const ChunkPos& pos, const StructureConfig& config) override;
//
//    StructureStart *createStart(int x, int z, const BoundingBox &bounds, int refCount, int64_t seed) override;
//};
#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct Stronghold {
    static auto create() -> std::unique_ptr<Structure>;
    static auto canGenerate(ChunkGenerator& generator, BiomeProvider& biomes, int64_t seed, Random& random, int x, int z, Biome& biome, const ChunkPos& pos, const StructureConfig& config) -> bool;
    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config);
};
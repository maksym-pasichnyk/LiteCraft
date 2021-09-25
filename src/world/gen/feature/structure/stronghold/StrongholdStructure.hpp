#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct StrongholdStructure : CfgStructure<> {
    StrongholdStructure() : CfgStructure(&StrongholdStructure::createComponents) {}

    bool canGenerate(ChunkGenerator& generator, BiomeProvider& biomes, int64_t seed, Random& random, int x, int z, Biome& biome, const ChunkPos& pos, const StructureConfig& config) override;

    static void createComponents(StructurePieces& pieces, ChunkGenerator &generator, TemplateManager &templateManager, int x, int z, Biome &biome, const StructureConfig &config, int64_t seed) {}
};
#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct OceanRuinStructure : CfgStructure<OceanRuinConfig> {
    OceanRuinStructure() : CfgStructure(&OceanRuinStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, ChunkGenerator &generator, TemplateManager &templateManager, int x, int z, Biome &biome, const StructureConfig &config, int64_t seed) {}
};
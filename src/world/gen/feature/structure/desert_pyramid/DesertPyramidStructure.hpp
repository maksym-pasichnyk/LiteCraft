#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct DesertPyramidStructure : CfgStructure<> {
    DesertPyramidStructure() : CfgStructure(&DesertPyramidStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, ChunkGenerator &generator, TemplateManager &templateManager, int x, int z, Biome &biome, const StructureConfig &config, int64_t seed);
};
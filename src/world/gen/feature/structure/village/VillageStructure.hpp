#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct VillageStructure : CfgStructure<JigsawConfig> {
    VillageStructure() : CfgStructure(&VillageStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config);
};
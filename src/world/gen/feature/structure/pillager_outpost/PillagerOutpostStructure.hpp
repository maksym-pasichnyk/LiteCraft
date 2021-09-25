#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct PillagerOutpostStructure : CfgStructure<JigsawConfig> {
    PillagerOutpostStructure() : CfgStructure(&PillagerOutpostStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
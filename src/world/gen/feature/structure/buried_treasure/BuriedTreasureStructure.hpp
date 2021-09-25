#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct BuriedTreasureStructure : CfgStructure<ProbabilityConfig> {
    BuriedTreasureStructure() : CfgStructure(&BuriedTreasureStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
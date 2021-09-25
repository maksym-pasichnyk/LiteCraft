#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct OceanRuinStructure : CfgStructure<OceanRuinConfig> {
    OceanRuinStructure() : CfgStructure(&OceanRuinStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
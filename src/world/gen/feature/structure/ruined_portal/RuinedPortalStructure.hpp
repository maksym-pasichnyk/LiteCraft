#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct RuinedPortalStructure : CfgStructure<RuinedPortalConfig> {
    RuinedPortalStructure() : CfgStructure(&RuinedPortalStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct WoodlandMansionStructure : CfgStructure<> {
    WoodlandMansionStructure() : CfgStructure(&WoodlandMansionStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
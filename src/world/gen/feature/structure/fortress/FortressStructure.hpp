#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct FortressStructure : CfgStructure<> {
    FortressStructure() : CfgStructure(&FortressStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
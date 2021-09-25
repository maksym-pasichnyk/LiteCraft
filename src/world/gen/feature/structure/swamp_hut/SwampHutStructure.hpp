#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct SwampHutStructure : CfgStructure<> {
    SwampHutStructure() : CfgStructure(&SwampHutStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config);
};
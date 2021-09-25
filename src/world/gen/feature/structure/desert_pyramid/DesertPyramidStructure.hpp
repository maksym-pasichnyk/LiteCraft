#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct DesertPyramidStructure : CfgStructure<> {
    DesertPyramidStructure() : CfgStructure(&DesertPyramidStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config);
};
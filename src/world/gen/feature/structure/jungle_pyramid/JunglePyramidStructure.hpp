#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct JunglePyramidStructure : CfgStructure<> {
    JunglePyramidStructure() : CfgStructure(&JunglePyramidStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config);
};
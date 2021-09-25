#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct IglooStructure : CfgStructure<> {
    IglooStructure() : CfgStructure(&IglooStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct EndCityStructure : CfgStructure<> {
    EndCityStructure() : CfgStructure(&EndCityStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
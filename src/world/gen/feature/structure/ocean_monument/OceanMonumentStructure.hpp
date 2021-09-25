#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct OceanMonumentStructure : CfgStructure<> {
    OceanMonumentStructure() : CfgStructure(&OceanMonumentStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
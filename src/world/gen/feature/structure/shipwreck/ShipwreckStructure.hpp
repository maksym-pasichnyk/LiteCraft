#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct ShipwreckStructure : CfgStructure<ShipwreckConfig> {
    ShipwreckStructure() : CfgStructure(&ShipwreckStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct BastionRemnantStructure : CfgStructure<JigsawConfig> {
    BastionRemnantStructure() : CfgStructure(&BastionRemnantStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
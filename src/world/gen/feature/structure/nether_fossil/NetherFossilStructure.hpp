#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct NetherFossilStructure : CfgStructure<> {
    NetherFossilStructure() : CfgStructure(&NetherFossilStructure::createComponents) {}

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};
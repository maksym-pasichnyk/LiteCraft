#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct DesertPyramid {
    static auto create() -> std::unique_ptr<Structure>;
    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config);
};
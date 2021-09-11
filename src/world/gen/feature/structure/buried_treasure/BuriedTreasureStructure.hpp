#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct BuriedTreasureStructure : CfgStructure<ProbabilityConfig> {
    struct Start;

    StructureStart *createStart(int x, int z, const BoundingBox &bounds, int refCount, int64_t seed) override;
};
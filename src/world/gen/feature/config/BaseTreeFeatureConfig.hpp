#pragma once

#include <vector>

#include "../FeatureSizeType.hpp"
#include "../../Heightmap.hpp"

struct FoliagePlacer;
struct TreeDecorator;
struct BlockStateProvider;
struct AbstractTrunkPlacer;
struct BaseTreeFeatureConfig {
    BlockStateProvider* trunkProvider = nullptr;
    BlockStateProvider* leavesProvider = nullptr;
    std::vector<TreeDecorator*> decorators{};
    bool forcePlacement = false;
    FoliagePlacer* foliagePlacer = nullptr;
    AbstractTrunkPlacer* trunkPlacer = nullptr;
    FeatureSizeType minimumSize;
    int maxWaterDepth = 0;
    bool ignoreVines = false;
    HeightmapType heightmap;
};
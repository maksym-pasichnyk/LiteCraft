#pragma once

#include "NoPlacementConfig.hpp"
#include "ChanceConfig.hpp"
#include "CaveEdgeConfig.hpp"
#include "DepthAverageConfig.hpp"
#include "TopSolidRangeConfig.hpp"
#include "NoiseDependantConfig.hpp"
#include "TopSolidWithNoiseConfig.hpp"
#include "AtSurfaceWithExtraConfig.hpp"
#include "DecoratedPlacementConfig.hpp"
#include "../../feature/config/FeatureSpreadConfig.hpp"

#include <variant>

using PlacementConfig = std::variant<
    NoPlacementConfig,
    ChanceConfig,
    CaveEdgeConfig,
    DepthAverageConfig,
    FeatureSpreadConfig,
    TopSolidRangeConfig,
    NoiseDependantConfig,
    TopSolidWithNoiseConfig,
    AtSurfaceWithExtraConfig,
    DecoratedPlacementConfig
>;
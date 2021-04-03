#pragma once

#include "NoFeatureConfig.hpp"
#include "OreFeatureConfig.hpp"
#include "DecoratedFeatureConfig.hpp"
#include "BlockClusterFeatureConfig.hpp"
#include "MultipleRandomFeatureConfig.hpp"

#include <variant>

using FeatureConfig = std::variant<
    NoFeatureConfig,
    OreFeatureConfig,
    DecoratedFeatureConfig,
    BlockClusterFeatureConfig,
    MultipleRandomFeatureConfig
>;
#pragma once

#include "NoFeatureConfig.hpp"
#include "DecoratedFeatureConfig.hpp"
#include "BlockClusterFeatureConfig.hpp"
#include "MultipleRandomFeatureConfig.hpp"

#include <variant>

using FeatureConfig = std::variant<
    NoFeatureConfig,
    DecoratedFeatureConfig,
    BlockClusterFeatureConfig,
    MultipleRandomFeatureConfig
>;
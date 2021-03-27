#pragma once

#include "NoFeatureConfig.hpp"
#include "BlockClusterFeatureConfig.hpp"
#include "DecoratedFeatureConfig.hpp"

#include <variant>

using FeatureConfig = std::variant<
    NoFeatureConfig,
    BlockClusterFeatureConfig,
    DecoratedFeatureConfig
>;
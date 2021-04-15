#pragma once

#include "MineshaftConfig.hpp"
#include "../../config/NoFeatureConfig.hpp"
#include "../../config/ProbabilityConfig.hpp"

#include <variant>

using StructureConfig = std::variant<
    NoFeatureConfig,
    MineshaftConfig,
    ProbabilityConfig
>;
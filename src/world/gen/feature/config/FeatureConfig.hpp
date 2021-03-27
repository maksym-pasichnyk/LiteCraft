#pragma once

#include "NoFeatureConfig.hpp"

#include <variant>

using FeatureConfig = std::variant<
    NoFeatureConfig
>;
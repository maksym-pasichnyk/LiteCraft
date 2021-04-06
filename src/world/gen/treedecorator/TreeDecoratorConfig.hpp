#pragma once

#include "../feature/config/ProbabilityConfig.hpp"
#include "../feature/config/BlockStateProvidingFeatureConfig.hpp"

#include <variant>

using TreeDecoratorConfig = std::variant<std::monostate, ProbabilityConfig,BlockStateProvidingFeatureConfig>;
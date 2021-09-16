#pragma once

#include "JigsawConfig.hpp"
#include "MineshaftConfig.hpp"
#include "OceanRuinConfig.hpp"
#include "RuinedPortalConfig.hpp"
#include "ShipwreckConfig.hpp"
#include <world/gen/feature/config/NoFeatureConfig.hpp>
#include <world/gen/feature/config/ProbabilityConfig.hpp>

#include <variant>

using StructureConfig = std::variant<
    NoFeatureConfig,
    JigsawConfig,
    MineshaftConfig,
    OceanRuinConfig,
    ShipwreckConfig,
    ProbabilityConfig,
    RuinedPortalConfig
>;
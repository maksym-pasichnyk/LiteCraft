#pragma once

#include "VillageConfig.hpp"
#include "MineshaftConfig.hpp"
#include "OceanRuinConfig.hpp"
#include "ShipwreckConfig.hpp"
#include "RuinedPortalConfig.hpp"
#include <world/gen/feature/config/NoFeatureConfig.hpp>
#include <world/gen/feature/config/ProbabilityConfig.hpp>

#include <variant>

using StructureConfig = std::variant<
    NoFeatureConfig,
    VillageConfig,
    MineshaftConfig,
    OceanRuinConfig,
    ShipwreckConfig,
    ProbabilityConfig,
    RuinedPortalConfig
>;
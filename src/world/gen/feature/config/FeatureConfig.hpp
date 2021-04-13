#pragma once

#include "NoFeatureConfig.hpp"
#include "OreFeatureConfig.hpp"
#include "ProbabilityConfig.hpp"
#include "SphereReplaceConfig.hpp"
#include "BaseTreeFeatureConfig.hpp"
#include "BlockWithContextConfig.hpp"
#include "DecoratedFeatureConfig.hpp"
#include "TwoFeatureChoiceConfig.hpp"
#include "BlockStateFeatureConfig.hpp"
#include "BigMushroomFeatureConfig.hpp"
#include "BlockClusterFeatureConfig.hpp"
#include "SingleRandomFeatureConfig.hpp"
#include "MultipleRandomFeatureConfig.hpp"
#include "BlockStateProvidingFeatureConfig.hpp"

#include <variant>

using FeatureConfig = std::variant<
    NoFeatureConfig,
    OreFeatureConfig,
    ProbabilityConfig,
    SphereReplaceConfig,
    BaseTreeFeatureConfig,
    BlockWithContextConfig,
    DecoratedFeatureConfig,
    TwoFeatureChoiceConfig,
    BlockStateFeatureConfig,
    BigMushroomFeatureConfig,
    BlockClusterFeatureConfig,
    SingleRandomFeatureConfig,
    MultipleRandomFeatureConfig,
    BlockStateProvidingFeatureConfig
>;
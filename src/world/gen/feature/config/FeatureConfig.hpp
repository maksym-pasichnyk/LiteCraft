#pragma once

#include "ColumnConfig.hpp"
#include "LiquidsConfig.hpp"
#include "NoFeatureConfig.hpp"
#include "FillLayerConfig.hpp"
#include "EndGatewayConfig.hpp"
#include "OreFeatureConfig.hpp"
#include "HugeFungusConfig.hpp"
#include "ProbabilityConfig.hpp"
#include "ReplaceBlockConfig.hpp"
#include "SphereReplaceConfig.hpp"
#include "BasaltDeltasFeature.hpp"
#include "EndSpikeFeatureConfig.hpp"
#include "BlobReplacementConfig.hpp"
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
    ColumnConfig,
    LiquidsConfig,
    FillLayerConfig,
    EndGatewayConfig,
    OreFeatureConfig,
    HugeFungusConfig,
    ProbabilityConfig,
    ReplaceBlockConfig,
    SphereReplaceConfig,
    BasaltDeltasFeature,
    EndSpikeFeatureConfig,
    BlobReplacementConfig,
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
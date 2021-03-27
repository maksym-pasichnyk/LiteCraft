#include "ConfiguredFeature.hpp"
#include "Feature.hpp"
#include "Features.hpp"
#include "config/DecoratedFeatureConfig.hpp"

#include "../ChunkGenerator.hpp"
#include "../placement/Placement.hpp"
#include "../placement/Placements.hpp"
#include "../../WorldGenRegion.hpp"

bool ConfiguredFeature::generate(WorldGenRegion &region, ChunkGenerator &generator, Random &random, glm::ivec3 pos) {
    return feature->generate(region, generator, random, pos, config);
}

ConfiguredFeature *ConfiguredFeature::withPlacement(ConfiguredPlacement *placement) {
    return Features::DECORATED->withConfiguration(DecoratedFeatureConfig{
        .feature = this,
        .placement = placement
    });
}

ConfiguredFeature *ConfiguredFeature::chance(int chance) {
    return withPlacement(Placements::CHANCE->withConfiguration(ChanceConfig{chance}));
}

ConfiguredFeature *ConfiguredFeature::range(int maximum) {
    return withPlacement(Placements::RANGE->withConfiguration(TopSolidRangeConfig{0, 0, maximum}));
}

ConfiguredFeature *ConfiguredFeature::square() {
    return withPlacement(Placements::SQUARE->withConfiguration(NoPlacementConfig{}));
}

ConfiguredFeature *ConfiguredFeature::withSpreadPlacement(FeatureSpread spread) {
    return withPlacement(Placements::COUNT->withConfiguration(FeatureSpreadConfig{spread}));
}


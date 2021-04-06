#include "ConfiguredPlacement.hpp"
#include "Placement.hpp"
#include "Placements.hpp"
#include "config/DecoratedPlacementConfig.hpp"

void ConfiguredPlacement::forEach(WorldGenRegion &region, Random &random, BlockPos pos, const std::function<void(BlockPos)>& fn) {
    placement->forEach(region, random, config, pos, fn);
}

ConfiguredPlacement *ConfiguredPlacement::withPlacement(ConfiguredPlacement *placement) {
    return new ConfiguredPlacement{
        .placement = Placements::DECORATED,
        .config = DecoratedPlacementConfig{
            .outer = placement,
            .inner = this
        }
    };
}

ConfiguredPlacement *ConfiguredPlacement::chance(int chance) {
    return withPlacement(Placements::CHANCE->withConfiguration(ChanceConfig{chance}));
}

ConfiguredPlacement *ConfiguredPlacement::range(int maximum) {
    return withPlacement(Placements::RANGE->withConfiguration(TopSolidRangeConfig{0, 0, maximum}));
}

ConfiguredPlacement *ConfiguredPlacement::square() {
    return withPlacement(Placements::SQUARE->withConfiguration(NoPlacementConfig{}));
}

ConfiguredPlacement *ConfiguredPlacement::withSpreadPlacement(FeatureSpread spread) {
    return withPlacement(Placements::COUNT->withConfiguration(FeatureSpreadConfig{spread}));
}
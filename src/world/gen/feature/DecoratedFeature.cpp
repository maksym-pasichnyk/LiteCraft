#include "DecoratedFeature.hpp"
#include "config/DecoratedFeatureConfig.hpp"
#include "../placement/ConfiguredPlacement.hpp"

bool DecoratedFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<DecoratedFeatureConfig>(config);
    bool flag = false;
    cfg.placement->forEach(reader, random, pos, [&flag, &cfg, &reader, &generator, &random] (BlockPos pos) {
        if (cfg.feature->generate(reader, generator, random, pos)) {
            flag = true;
        }
    });
    return flag;
}

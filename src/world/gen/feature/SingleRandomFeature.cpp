#include "SingleRandomFeature.hpp"

bool SingleRandomFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<SingleRandomFeatureConfig>(config);
    const auto feature = random.nextElement(std::span(cfg.features));
    return feature->generate(reader, generator, random, pos);
}

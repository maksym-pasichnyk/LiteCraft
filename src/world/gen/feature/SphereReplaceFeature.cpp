#include "SphereReplaceFeature.hpp"

bool SphereReplaceFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    return AbstractSphereReplaceFeature::generate(reader, generator, random, pos, config);
}

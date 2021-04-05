#include "TwoFeatureChoiceFeature.hpp"

bool TwoFeatureChoiceFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, glm::ivec3 pos, const FeatureConfig &config) {
    const auto& cfg = std::get<TwoFeatureChoiceConfig>(config);
    return random.nextBoolean()
        ? cfg.feature_true->generate(reader, generator, random, pos)
        : cfg.feature_false->generate(reader, generator, random, pos);
}

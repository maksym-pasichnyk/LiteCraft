#include "MultipleWithChanceRandomFeature.hpp"

bool MultipleWithChanceRandomFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, glm::ivec3 pos, const FeatureConfig &config) {
    const auto& cfg = std::get<MultipleRandomFeatureConfig>(config);
    for(const auto [feature, chance] : cfg.features) {
        if (random.nextFloat() < chance) {
            return feature->generate(reader, generator, random, pos);
        }
    }
    return cfg.defaultFeature->generate(reader, generator, random, pos);
}

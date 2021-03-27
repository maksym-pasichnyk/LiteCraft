#include "ConfiguredFeature.hpp"
#include "Feature.hpp"

#include "../ChunkGenerator.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../util/Random.hpp"

void ConfiguredFeature::generate(WorldGenRegion &region, ChunkGenerator &generator, Random &random, glm::ivec3 pos) {
    feature->generate(region, generator, random, pos, config);
}

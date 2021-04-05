#include "BambooFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"

BambooFeature::BambooFeature() {
    BAMBOO = Blocks::BAMBOO->getDefaultState();
    BAMBOO_BASE = BAMBOO;//.with(PROPERTY_AGE, 1).with(PROPERTY_BAMBOO_LEAVES, BambooLeaves.NONE).with(PROPERTY_STAGE, 0);
    BAMBOO_LARGE_LEAVES_GROWN = BAMBOO_BASE;//.with(PROPERTY_BAMBOO_LEAVES, BambooLeaves.LARGE).with(PROPERTY_STAGE, 1);
    BAMBOO_LARGE_LEAVES = BAMBOO_BASE;//.with(PROPERTY_BAMBOO_LEAVES, BambooLeaves.LARGE);
    BAMBOO_SMALL_LEAVES = BAMBOO_BASE;//.with(PROPERTY_BAMBOO_LEAVES, BambooLeaves.SMALL);
}

bool BambooFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, glm::ivec3 pos, const FeatureConfig &config) {
    if (!reader.isAirBlock(pos)) {
        return false;
    }
    if (!BAMBOO.isValidPosition(reader, pos)) {
        return false;
    }

    const auto& cfg = std::get<ProbabilityConfig>(config);

    const int height = random.nextInt(12) + 5;
    if (random.nextFloat() < cfg.probability) {
        int k = random.nextInt(4) + 1;

        for(int l = pos.x - k; l <= pos.x + k; ++l) {
            for(int i1 = pos.z - k; i1 <= pos.z + k; ++i1) {
                const int j1 = l - pos.x;
                const int k1 = i1 - pos.z;
                if (j1 * j1 + k1 * k1 <= k * k) {
                    const auto y = reader.getHeight(HeightmapType::WORLD_SURFACE, l, i1);
                    const glm::ivec3 blockpos(l, y, i1);
                    if (isDirt(reader.getData(blockpos).getBlock())) {
                        reader.setData(blockpos, Blocks::PODZOL->getDefaultState()/*, 2*/);
                    }
                }
            }
        }
    }

    glm::ivec3 blockpos = pos;
    for (int l1 = 0; l1 < height && reader.isAirBlock(blockpos); ++l1) {
        reader.setData(blockpos, BAMBOO_BASE/*, 2*/);
        blockpos.y += 1;
    }

    if (blockpos.y - pos.y >= 3) {
        reader.setData(blockpos, BAMBOO_LARGE_LEAVES_GROWN/*, 2*/);
        reader.setData(blockpos -= glm::ivec3(0, 1, 0), BAMBOO_LARGE_LEAVES/*, 2*/);
        reader.setData(blockpos -= glm::ivec3(0, 1, 0), BAMBOO_SMALL_LEAVES/*, 2*/);
    }

    return true;
}
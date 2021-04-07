#include "BlockBlobFeature.hpp"
#include "../../WorldGenRegion.hpp"

bool BlockBlobFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<BlockStateFeatureConfig>(config);
    while(true) {
        if (pos.y > 3) {
            if (reader.isAirBlock(pos.down())) {
                pos = pos.down();
                continue;
            }

            auto block = reader.getData(pos.down()).getBlock();
            if (!(isDirt(block) || isStone(block))) {
                pos = pos.down();
                continue;
            }
        }

        if (pos.y <= 3) {
            return false;
        }

        for (int l = 0; l < 3; ++l) {
            int i = random.nextInt(2);
            int j = random.nextInt(2);
            int k = random.nextInt(2);
            float f = (float)(i + j + k) * 0.333F + 0.5F;

            for (BlockPos blockpos : BlockPos::getAllInBox(pos - glm::ivec3(i, j, k), pos + glm::ivec3(i, j, k))) {
                if (blockpos.distanceSq(pos) <= (double)(f * f)) {
                    reader.setData(blockpos, cfg.state/*, 4*/);
                }
            }

            pos = pos + glm::ivec3(random.nextInt(2) - 1, -random.nextInt(2), random.nextInt(2) - 1);
        }

        return true;
    }
}

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

        for (int i = 0; i < 3; ++i) {
            const auto xrange = random.nextInt(2);
            const auto yrange = random.nextInt(2);
            const auto zrange = random.nextInt(2);
            const auto dist = static_cast<float>(xrange + yrange + zrange) * 0.333F + 0.5F;

            for (const auto blockpos : BlockPos::getAllInBox(pos.sub(xrange, yrange, zrange), pos.add(xrange, yrange, zrange))) {
                if (blockpos.distanceSq(pos) <= static_cast<double>(dist * dist)) {
                    reader.setData(blockpos, cfg.state/*, 4*/);
                }
            }

            const auto dx = random.nextInt(2);
            const auto dy = random.nextInt(2);
            const auto dz = random.nextInt(2);
            pos = pos.sub(1 - dx, dy, 1 - dz);
        }

        return true;
    }
}

#include "EndIslandFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool EndIslandFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    auto radius = static_cast<float>(random.nextInt(3) + 4);

    for (int dy = 0; radius > 0.5F; --dy) {
        for (int dx = static_cast<int>(std::floor(-radius)); dx <= static_cast<int>(std::ceil(radius)); ++dx) {
            for (int dz = static_cast<int>(std::floor(-radius)); dz <= static_cast<int>(std::ceil(radius)); ++dz) {
                if (static_cast<float>(dx * dx + dz * dz) <= (radius + 1.0F) * (radius + 1.0F)) {
                    setBlockState(reader, pos.add(dx, dy, dz), Blocks::END_STONE->getDefaultState());
                }
            }
        }
        radius -= static_cast<float>(random.nextInt(2)) + 0.5f;
    }

    return true;
}
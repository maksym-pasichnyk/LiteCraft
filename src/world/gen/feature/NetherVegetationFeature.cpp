#include "NetherVegetationFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>
#include <world/gen/blockstateprovider/BlockStateProvider.hpp>

bool NetherVegetationFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    return place(reader, random, pos, std::get<BlockStateProvidingFeatureConfig>(config), 8, 4);
}

bool NetherVegetationFeature::place(WorldGenRegion &reader, Random& random, const BlockPos& start, const BlockStateProvidingFeatureConfig& config, int xz_range, int y_range) {
    if (start.y >= 1 && start.y < 255) {
        auto block = reader.getData(start.down()).getBlock();
        if (!block->isIn(BlockTags::NYLIUM)) {
            return false;
        }
        
        int count = 0;

        for (int i = 0; i < xz_range * xz_range; ++i) {
            const auto x0 = random.nextInt(xz_range);
            const auto x1 = random.nextInt(xz_range);
            const auto y0 = random.nextInt(y_range);
            const auto y1 = random.nextInt(y_range);
            const auto z0 = random.nextInt(xz_range);
            const auto z1 = random.nextInt(xz_range);
            const auto pos = start.add(x0 - x1, y0 - y1, z0 - z1);
            const auto state = config.stateProvider->getBlockState(random, pos);
            if (reader.isAirBlock(pos) && pos.y > 0 && state.isValidPosition(reader, pos)) {
                reader.setData(pos, state/*, 2*/);
                ++count;
            }
        }

        return count > 0;
    }
    
    return false;
}

#include "BlockPileFeature.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldReader.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../util/math/BlockPos.hpp"

static bool canPlaceOn(WorldReader& worldIn, const BlockPos& pos, Random& random) {
    const auto blockpos = pos.down();
    const auto state = worldIn.getData(blockpos);
    return state.is(Blocks::GRASS_PATH) && random.nextBoolean();
//        ? random.nextBoolean()
//        : state.isSolidSide(worldIn, blockpos, Direction.UP);
}

static void placeBlock(WorldGenRegion &reader, const BlockPos& pos, Random& random, const BlockStateProvidingFeatureConfig& config) {
    if (reader.isAirBlock(pos) && canPlaceOn(reader, pos, random)) {
        reader.setData(pos, config.stateProvider->getBlockState(random, pos)/*, 4*/);
    }
}

bool BlockPileFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto &cfg = std::get<BlockStateProvidingFeatureConfig>(config);
    if (pos.y < 5) {
        return false;
    }
    const int i = 2 + random.nextInt(2);
    const int j = 2 + random.nextInt(2);

    const auto from = pos - BlockPos(i, 0, j);
    const auto to = pos + BlockPos(i, 1, j);
    for (BlockPos blockpos : BlockPos::getAllInBox(from, to)) {
        const int dx = pos.x - blockpos.x;
        const int dz = pos.z - blockpos.z;
        const float a = random.nextFloat() * 10.0F;
        if (static_cast<float>(dx * dx + dz * dz) <= (a - random.nextFloat() * 6.0F)) {
            placeBlock(reader, blockpos, random, cfg);
        } else if (random.nextFloat() < 0.031f) {
            placeBlock(reader, blockpos, random, cfg);
        }
    };


    return true;
}
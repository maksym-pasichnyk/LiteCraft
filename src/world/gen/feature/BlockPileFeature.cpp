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
    const auto xrange = 2 + random.nextInt(2);
    const auto zrange = 2 + random.nextInt(2);

    for (const auto blockpos : BlockPos::getAllInBox(pos.sub(xrange, 0, zrange), pos.add(xrange, 1, zrange))) {
        const auto dx = pos.x - blockpos.x;
        const auto dz = pos.z - blockpos.z;
        const auto a = random.nextFloat() * 10.0F;
        if (static_cast<float>(dx * dx + dz * dz) <= (a - random.nextFloat() * 6.0F)) {
            placeBlock(reader, blockpos, random, cfg);
        } else if (random.nextFloat() < 0.031f) {
            placeBlock(reader, blockpos, random, cfg);
        }
    };


    return true;
}
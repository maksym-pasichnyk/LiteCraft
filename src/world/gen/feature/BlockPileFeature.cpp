#include "BlockPileFeature.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldReader.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../util/math/BlockPos.hpp"

static bool canPlaceOn(WorldReader& worldIn, const glm::ivec3& pos, Random& random) {
    const auto blockpos = pos - glm::ivec3(0, 1, 0);
    const auto state = worldIn.getData(blockpos);
    return state.isIn(Blocks::GRASS_PATH) && random.nextBoolean();
//        ? random.nextBoolean()
//        : state.isSolidSide(worldIn, blockpos, Direction.UP);
}

static void placeBlock(WorldGenRegion &reader, const glm::ivec3& pos, Random& random, const BlockStateProvidingFeatureConfig& config) {
    if (reader.isAirBlock(pos) && canPlaceOn(reader, pos, random)) {
        reader.setData(pos, config.stateProvider->getBlockState(random, pos)/*, 4*/);
    }
}

bool BlockPileFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, glm::ivec3 pos, const FeatureConfig &config) {
    const auto &cfg = std::get<BlockStateProvidingFeatureConfig>(config);
    if (pos.y < 5) {
        return false;
    }
    const int i = 2 + random.nextInt(2);
    const int j = 2 + random.nextInt(2);

    const auto from = pos - glm::ivec3(i, 0, j);
    const auto to = pos + glm::ivec3(i, 1, j);
    BlockPos::getAllInBoxMutable(from, to, [&reader, &cfg, &random, pos] (const glm::ivec3 &blockpos) {
        const int dx = pos.x - blockpos.x;
        const int dz = pos.z - blockpos.z;
        if (static_cast<float>(dx * dx + dz * dz) <= (random.nextFloat() * 10.0F - random.nextFloat() * 6.0F)) {
            placeBlock(reader, blockpos, random, cfg);
        } else if (random.nextFloat() < 0.031f) {
            placeBlock(reader, blockpos, random, cfg);
        }
    });


    return true;
}
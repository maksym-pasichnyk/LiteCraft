#include "BasaltDeltasStructure.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

std::set<Block*> BasaltDeltasStructure::blacklist{};

BasaltDeltasStructure::BasaltDeltasStructure() {
    blacklist = {
        Blocks::BEDROCK,
        Blocks::NETHER_BRICKS,
        Blocks::NETHER_BRICK_FENCE,
        Blocks::NETHER_BRICK_STAIRS,
        Blocks::NETHER_WART,
        Blocks::CHEST,
        Blocks::SPAWNER
    };
}

bool BasaltDeltasStructure::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<BasaltDeltasFeature>(config);

    auto flag = false;
    auto flag1 = random.nextDouble() < 0.9;
    auto dx = flag1 ? cfg.rim_size.get(random) : 0;
    auto dz = flag1 ? cfg.rim_size.get(random) : 0;
    auto flag2 = flag1 && dx != 0 && dz != 0;
    auto k = cfg.size.get(random);
    auto l = cfg.size.get(random);
    auto i1 = std::max(k, l);
//
//    for (const auto blockpos : BlockPos::getProximitySortedBoxPositionsIterator(pos, k, 0, l)) {
//        if (blockpos.manhattanDistance(pos) > i1) {
//            break;
//        }
//
//        if (func_236277_a_(reader, blockpos, cfg)) {
//            if (flag2) {
//                flag = true;
//                setBlockState(reader, blockpos, cfg.rim;
//            }
//
//            const auto blockpos1 = blockpos.add(dx, 0, dz);
//            if (func_236277_a_(reader, blockpos1, cfg)) {
//                flag = true;
//                setBlockState(reader, blockpos1, cfg.contents);
//            }
//        }
//    }

    return flag;
}

bool BasaltDeltasStructure::func_236277_a_(WorldGenRegion &reader, BlockPos pos, const BasaltDeltasFeature &config) {
    const auto state = reader.getData(pos);
    if (state.is(config.contents.getBlock())) {
        return false;
    }
    if (blacklist.contains(state.getBlock())) {
        return false;
    }
    for (const auto direction : DirectionUtil::values()) {
        const auto flag = reader.getData(pos.offset(direction)).isAir();
        if (flag && direction != Direction::UP || !flag && direction == Direction::UP) {
            return false;
        }
    }

    return true;
}

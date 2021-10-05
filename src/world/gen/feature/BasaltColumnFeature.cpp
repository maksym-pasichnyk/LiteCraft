#include "BasaltColumnFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

std::set<Block*> BasaltColumnFeature::blacklist{};

BasaltColumnFeature::BasaltColumnFeature() {
    blacklist = {
        Blocks::LAVA, 
        Blocks::BEDROCK, 
        Blocks::MAGMA_BLOCK, 
        Blocks::SOUL_SAND,
        Blocks::NETHER_BRICKS, 
        Blocks::NETHER_BRICK_FENCE, 
        Blocks::NETHER_BRICK_STAIRS, 
        Blocks::NETHER_WART, 
        Blocks::CHEST, 
        Blocks::SPAWNER
    };
}

bool BasaltColumnFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto &cfg = std::get<ColumnConfig>(config);

    const auto max_y = reader.getSeaLevel();
    if (func_242762_a(reader, max_y, pos)) {
        const auto height = cfg.height.get(random);
        const auto flag = random.nextFloat() < 0.9F;
        const auto k = std::min(height, flag ? 5 : 8);
        const auto l = flag ? 50 : 15;
        auto flag1 = false;

//        for (const auto blockpos : BlockPos::getRandomPositions(rand, l, pos.x - k, pos.y, pos.z - k, pos.x + k, pos.y, pos.z + k)) {
//            int i1 = height - blockpos.manhattanDistance(pos);
//            if (i1 >= 0) {
//                if (func_236248_a_(reader, max_y, blockpos, i1, cfg.func_242794_am_().func_242259_a(rand))) {
//                    flag1 = true;
//                }
//            }
//        }

        return flag1;
    }
    return false;
}

bool BasaltColumnFeature::func_236248_a_(WorldGenRegion &reader, int max_y, const BlockPos &start, int p_236248_4_, int xz_range) {
    bool flag = false;

    for (const auto pos : BlockPos::getAllInBox(start.sub(xz_range, 0, xz_range), start.add(xz_range, 0, xz_range))) {
//        const auto dist = pos.manhattanDistance(start);
//        const auto lowest = func_236247_a_(reader, max_y, pos)
//                                   ? func_236246_a_(reader, max_y, pos, dist)
//                                   : func_236249_a_(reader, pos, dist);
//
//        if (lowest.has_value()) {
//            const auto j = p_236248_4_ - dist / 2;
//
//            for (auto blockpos = *lowest; j >= 0; --j, blockpos = blockpos.up()) {
//                if (func_236247_a_(reader, max_y, blockpos)) {
//                    setBlockState(reader, blockpos, States::BASALT);
//                    flag = true;
//                } else if (!reader.getBlockState(blockpos).in(Blocks::BASALT)) {
//                    break;
//                }
//            }
//        }
    }
    return flag;
}

auto BasaltColumnFeature::func_236246_a_(WorldGenRegion &reader, int max_y, const BlockPos &start, int count) -> std::optional<BlockPos> {
    auto pos = start;
    for (int i = count; pos.y > 1 && i > 0; --i, pos = pos.down()) {
        if (func_242762_a(reader, max_y, pos)) {
            return pos;
        }
    }
    return std::nullopt;
}

auto BasaltColumnFeature::func_236249_a_(WorldGenRegion &reader, const BlockPos &start, int count) -> std::optional<BlockPos> {
    auto pos = start;
    
    for (int i = count; pos.y < /*reader.getHeight()*/256 && i > 0; --i, pos = pos.up()) {
        const auto state = reader.getData(pos);
        if (blacklist.contains(state.getBlock())) {
            return std::nullopt;
        }

        if (state.isAir()) {
            return pos;
        }
    }

    return std::nullopt;
}

bool BasaltColumnFeature::func_242762_a(WorldGenRegion &reader, int max_y, const BlockPos &pos) {
    if (func_236247_a_(reader, max_y, pos)) {
        const auto state = reader.getData(pos.down());
        return !state.isAir() && !blacklist.contains(state.getBlock());
    }
    return false;
}

bool BasaltColumnFeature::func_236247_a_(WorldGenRegion &reader, int max_y, const BlockPos &pos) {
    const auto state = reader.getData(pos);
    return state.isAir() || state.is(Blocks::LAVA) && pos.y <= max_y;
}
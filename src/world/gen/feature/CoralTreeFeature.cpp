#include "CoralTreeFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool CoralTreeFeature::generate(WorldGenRegion& reader, Random& random, const BlockPos& pos, BlockData state) {
    auto lowest = pos;
    const auto height = random.nextInt(3) + 1;

    for (int i = 0; i < height; ++i) {
        if (!generateCorals(reader, random, lowest, state)) {
            return true;
        }
        lowest = lowest.up();
    }

    auto directions = DirectionUtil::Plane::HORIZONTAL;
//    Collections.shuffle(directions, random);

    for (const auto direction : std::span(directions).subspan(0, random.nextInt(3) + 2)) {
        auto blockpos = lowest.offset(direction);
        const auto distance = random.nextInt(5) + 2;
        int len = 0;

        for (int i = 0; i < distance && generateCorals(reader, random, blockpos, state); ++i) {
            ++len;
            blockpos = blockpos.up();
            if (i == 0 || len >= 2 && random.nextFloat() < 0.25F) {
                blockpos = blockpos.offset(direction);
                len = 0;
            }
        }
    }

    return true;
}
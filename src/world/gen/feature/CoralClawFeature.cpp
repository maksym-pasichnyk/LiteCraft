#include "CoralClawFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool CoralClawFeature::generate(WorldGenRegion& reader, Random& random, const BlockPos& pos, BlockData state) {
    if (!generateCorals(reader, random, pos, state)) {
        return false;
    }

    const auto start_direction = random.nextElement(std::span(DirectionUtil::Plane::HORIZONTAL));
    std::array directions{
        start_direction,
        DirectionUtil::rotateY(start_direction),
        DirectionUtil::rotateYCCW(start_direction)
    };
    //    Collections.shuffle(directions, random);

    for (const auto direction : std::span(directions).subspan(0, random.nextInt(2) + 2)) {
        auto blockpos = pos.offset(start_direction);
        const auto j = random.nextInt(2) + 1;
        int k;
        Direction grow_direction;
        if (direction == start_direction) {
            grow_direction = start_direction;
            k = random.nextInt(3) + 2;
        } else {
            blockpos = blockpos.up();
            const std::array directions_2{
                direction,
                Direction::UP
            };
            grow_direction = random.nextElement(std::span(directions_2));
            k = random.nextInt(3) + 3;
        }

        for (int i = 0; i < j && generateCorals(reader, random, blockpos, state); ++i) {
            blockpos = blockpos.offset(grow_direction);
        }

        blockpos = blockpos.offset(DirectionUtil::getOpposite(grow_direction)).up();

        for (int i = 0; i < k; ++i) {
            blockpos = blockpos.offset(start_direction);
            if (!generateCorals(reader, random, blockpos, state)) {
                break;
            }

            if (random.nextFloat() < 0.25F) {
                blockpos = blockpos.up();
            }
        }
    }
    return true;
}
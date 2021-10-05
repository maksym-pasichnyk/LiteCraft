#include "BlueIceFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <block/States.hpp>
#include <block/material/Materials.hpp>
#include "../../../util/Direction.hpp"
#include "../../WorldGenRegion.hpp"

bool BlueIceFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    if (pos.y > reader.getSeaLevel() - 1) {
        return false;
    }
    if (!reader.getData(pos).is(Blocks::WATER) && !reader.getData(pos.down()).is(Blocks::WATER)) {
        return false;
    }

    bool flag = false;
    for (Direction direction : DirectionUtil::values()) {
        if (direction != Direction::DOWN && reader.getData(pos.offset(direction)).is(Blocks::PACKED_ICE)) {
            flag = true;
            break;
        }
    }

    if (!flag) {
        return false;
    }

    reader.setData(pos, States::BLUE_ICE/*, 2*/);

    for (int i = 0; i < 200; ++i) {
        const auto g0 = random.nextInt(5);
        const auto j = g0 - random.nextInt(6);
        int k = 3;
        if (j < 2) {
            k += j / 2;
        }

        if (k >= 1) {
            const auto dx0 = random.nextInt(k);
            const auto dx1 = random.nextInt(k);
            const auto dx2 = random.nextInt(k);
            const auto dx3 = random.nextInt(k);

            const auto blockpos = pos.add(dx0 - dx1, j, dx2 - dx3);
            const auto state = reader.getData(blockpos);
            if (state.getMaterial() == Materials::AIR || state.is(Blocks::WATER) || state.is(Blocks::PACKED_ICE) || state.is(Blocks::ICE)) {
                for (const auto direction : DirectionUtil::values()) {
                    if (reader.getData(blockpos.offset(direction)).is(Blocks::BLUE_ICE)) {
                        reader.setData(blockpos, States::BLUE_ICE/*, 2*/);
                        break;
                    }
                }
            }
        }
    }

    return true;
}

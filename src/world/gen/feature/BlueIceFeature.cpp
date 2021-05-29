#include "BlueIceFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/material/Materials.hpp"
#include "../../../util/Direction.hpp"

bool BlueIceFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    if (pos.y > reader.getSeaLevel() - 1) {
        return false;
    }
    if (!reader.getData(pos).isIn(Blocks::WATER) && !reader.getData(pos.down()).isIn(Blocks::WATER)) {
        return false;
    }

    bool flag = false;
    for (Direction direction : DirectionUtil::values()) {
        if (direction != Direction::DOWN && reader.getData(pos.offset(direction)).isIn(Blocks::PACKED_ICE)) {
            flag = true;
            break;
        }
    }

    if (!flag) {
        return false;
    }

    const auto BLUE_ICE = Blocks::BLUE_ICE->getDefaultState();

    reader.setData(pos, BLUE_ICE/*, 2*/);

    for (int i = 0; i < 200; ++i) {
        const int g0 = random.nextInt(5);
        const int j = g0 - random.nextInt(6);
        int k = 3;
        if (j < 2) {
            k += j / 2;
        }

        if (k >= 1) {
            const int dx0 = random.nextInt(k);
            const int dx1 = random.nextInt(k);
            const int dx2 = random.nextInt(k);
            const int dx3 = random.nextInt(k);

            const BlockPos blockpos = pos + BlockPos(dx0 - dx1, j, dx2 - dx3);
            const auto state = reader.getData(blockpos);
            if (state.getMaterial() == Materials::AIR ||
                state.isIn(Blocks::WATER) ||
                state.isIn(Blocks::PACKED_ICE) ||
                state.isIn(Blocks::ICE)) {
                for (Direction direction : DirectionUtil::values()) {
                    if (reader.getData(blockpos.offset(direction)).isIn(Blocks::BLUE_ICE)) {
                        reader.setData(blockpos, BLUE_ICE/*, 2*/);
                        break;
                    }
                }
            }
        }
    }

    return true;
}

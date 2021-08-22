#include "AlterGroundTreeDecorator.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../feature/Feature.hpp"
#include "../../WorldGenRegion.hpp"

void AlterGroundTreeDecorator::decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) {
    const int y = positions1[0].y;
    for (const auto &pos : positions1) {
        if (pos.y == y) {
            placeBlocks(reader, random, pos.west().north());
            placeBlocks(reader, random, pos.east(2).north());
            placeBlocks(reader, random, pos.west().south(2));
            placeBlocks(reader, random, pos.east(2).south(2));

            for (int i = 0; i < 5; ++i) {
                const int k = random.nextInt(64);
                const int x = k % 8;
                const int z = k / 8;
                if (x == 0 || x == 7 || z == 0 || z == 7) {
                    placeBlocks(reader, random, pos.add(x - 3, 0, z - 3));
                }
            }
        }
    }
}

void AlterGroundTreeDecorator::placeColumn(WorldGenRegion &reader, Random &random, const BlockPos &pos) {
    for (int y = 2; y >= -3; --y) {
        auto blockpos = pos.up(y);
        if (Feature::isDirtAt(reader, blockpos)) {
            reader.setData(blockpos, provider->getBlockState(random, pos)/*, 19*/);
            break;
        }

        if (!Feature::isAirAt(reader, blockpos) && y < 0) {
            break;
        }
    }
}

void AlterGroundTreeDecorator::placeBlocks(WorldGenRegion &reader, Random &random, const BlockPos &pos) {
    for (int x = -2; x <= 2; ++x) {
        for (int z = -2; z <= 2; ++z) {
            if (std::abs(x) != 2 || std::abs(z) != 2) {
                placeColumn(reader, random, pos.add(x, 0, z));
            }
        }
    }
}

#include "LeaveVineTreeDecorator.hpp"
#include "../feature/Feature.hpp"
#include "../../WorldGenRegion.hpp"
#include <block/VineBlock.hpp>

void LeaveVineTreeDecorator::placeVines(WorldGenRegion& reader, const BlockPos& pos, BlockStateProperty property, std::set<BlockPos>& positions, BoundingBox& boundingBox) {
    placeVine(reader, pos, property, positions, boundingBox);

    auto blockpos = pos.down();
    for (int i = 4; i > 0 && Feature::isAirAt(reader, blockpos); --i) {
        placeVine(reader, blockpos, property, positions, boundingBox);
        blockpos.y--;
    }
}

void LeaveVineTreeDecorator::decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) {
    for (const auto& pos : positions2) {
        if (random.nextInt(4) == 0) {
            const auto blockpos = pos.west();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVines(reader, blockpos, VineBlock::EAST, positions3, boundingBox);
            }
        }

        if (random.nextInt(4) == 0) {
            const auto blockpos = pos.east();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVines(reader, blockpos, VineBlock::WEST, positions3, boundingBox);
            }
        }

        if (random.nextInt(4) == 0) {
            const auto blockpos = pos.north();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVines(reader, blockpos, VineBlock::SOUTH, positions3, boundingBox);
            }
        }

        if (random.nextInt(4) == 0) {
            const auto blockpos = pos.south();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVines(reader, blockpos, VineBlock::NORTH, positions3, boundingBox);
            }
        }
    }
}

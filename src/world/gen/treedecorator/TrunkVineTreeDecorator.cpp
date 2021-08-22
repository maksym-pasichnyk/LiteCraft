#include "TrunkVineTreeDecorator.hpp"
#include "../feature/Feature.hpp"
#include "../../WorldGenRegion.hpp"
#include <block/VineBlock.hpp>

void TrunkVineTreeDecorator::decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) {
    for (auto const& pos : positions1) {
        if (random.nextInt(3) > 0) {
            const auto blockpos = pos.west();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVine(reader, blockpos, VineBlock::EAST, positions3, boundingBox);
            }
        }

        if (random.nextInt(3) > 0) {
            const auto blockpos = pos.east();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVine(reader, blockpos, VineBlock::WEST, positions3, boundingBox);
            }
        }

        if (random.nextInt(3) > 0) {
            const auto blockpos = pos.north();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVine(reader, blockpos, VineBlock::SOUTH, positions3, boundingBox);
            }
        }

        if (random.nextInt(3) > 0) {
            const auto blockpos = pos.south();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVine(reader, blockpos, VineBlock::NORTH, positions3, boundingBox);
            }
        }
    }
}

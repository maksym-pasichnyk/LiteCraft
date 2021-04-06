#include "TrunkVineTreeDecorator.hpp"
#include "../feature/Feature.hpp"
#include "../../WorldGenRegion.hpp"

void TrunkVineTreeDecorator::decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) {
    for (auto const& pos : positions1) {
        if (random.nextInt(3) > 0) {
            BlockPos blockpos = pos.west();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVine(reader, blockpos/*, VineBlock::EAST*/, positions3, boundingBox);
            }
        }

        if (random.nextInt(3) > 0) {
            BlockPos blockpos1 = pos.east();
            if (Feature::isAirAt(reader, blockpos1)) {
                placeVine(reader, blockpos1/*, VineBlock::WEST*/, positions3, boundingBox);
            }
        }

        if (random.nextInt(3) > 0) {
            BlockPos blockpos2 = pos.north();
            if (Feature::isAirAt(reader, blockpos2)) {
                placeVine(reader, blockpos2/*, VineBlock::SOUTH*/, positions3, boundingBox);
            }
        }

        if (random.nextInt(3) > 0) {
            BlockPos blockpos3 = pos.south();
            if (Feature::isAirAt(reader, blockpos3)) {
                placeVine(reader, blockpos3/*, VineBlock::NORTH*/, positions3, boundingBox);
            }
        }
    }
}

#include "LeaveVineTreeDecorator.hpp"
#include "../feature/Feature.hpp"
#include "../../WorldGenRegion.hpp"

void LeaveVineTreeDecorator::placeVines(WorldGenRegion& reader, const BlockPos& pos/*, BooleanProperty p_227420_3_*/, std::set<BlockPos>& p_227420_4_, BoundingBox& boundingBox) {
    placeVine(reader, pos/*, p_227420_3_*/, p_227420_4_, boundingBox);

    auto blockpos = pos.down();
    for (int i = 4; i > 0 && Feature::isAirAt(reader, blockpos); --i) {
        placeVine(reader, blockpos/*, p_227420_3_*/, p_227420_4_, boundingBox);
        blockpos.y--;
    }
}

void LeaveVineTreeDecorator::decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) {
    for (const auto& pos : positions2) {
        if (random.nextInt(4) == 0) {
            const auto blockpos = pos.west();
            if (Feature::isAirAt(reader, blockpos)) {
                placeVines(reader, blockpos/*, VineBlock::EAST*/, positions3, boundingBox);
            }
        }

        if (random.nextInt(4) == 0) {
            const auto blockpos1 = pos.east();
            if (Feature::isAirAt(reader, blockpos1)) {
                placeVines(reader, blockpos1/*, VineBlock::WEST*/, positions3, boundingBox);
            }
        }

        if (random.nextInt(4) == 0) {
            const auto blockpos2 = pos.north();
            if (Feature::isAirAt(reader, blockpos2)) {
                placeVines(reader, blockpos2/*, VineBlock::SOUTH*/, positions3, boundingBox);
            }
        }

        if (random.nextInt(4) == 0) {
            const auto blockpos3 = pos.south();
            if (Feature::isAirAt(reader, blockpos3)) {
                placeVines(reader, blockpos3/*, VineBlock::NORTH*/, positions3, boundingBox);
            }
        }
    }
}

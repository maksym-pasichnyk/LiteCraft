#include "CocoaTreeDecorator.hpp"
#include "../feature/Feature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../util/Direction.hpp"

void CocoaTreeDecorator::decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) {
    if (random.nextFloat() < probability) {
        int y = positions1[0].y;

        for (const auto &pos : positions1) {
            if (pos.y <= y + 2) {
                for (Direction direction : Directions::Plane::HORIZONTAL) {
                    if (random.nextFloat() <= 0.25F) {
                        const auto direction1 = Directions::getOpposite(direction);
                        const auto blockpos = pos + BlockPos(Directions::getXOffset(direction1), 0, Directions::getZOffset(direction1));
                        if (Feature::isAirAt(reader, blockpos)) {
                            const auto state = Blocks::COCOA->getDefaultState();
//                                    .with(CocoaBlock::AGE, random.nextInt(3))
//                                    .with(CocoaBlock::HORIZONTAL_FACING, direction);
                            TreeDecorator::placeBlock(reader, blockpos, state, positions3, boundingBox);
                        }
                    }
                }
            }
        }
    }
}

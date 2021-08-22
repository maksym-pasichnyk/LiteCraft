#include "CocoaTreeDecorator.hpp"
#include "../feature/Feature.hpp"
#include "../../WorldGenRegion.hpp"
#include <block/Blocks.hpp>
#include <block/CocoaBlock.hpp>

void CocoaTreeDecorator::decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) {
    if (random.nextFloat() < probability) {
        const auto y = positions1[0].y;

        for (const auto &pos : positions1) {
            if (pos.y <= y + 2) {
                for (const auto direction : DirectionUtil::Plane::HORIZONTAL) {
                    if (random.nextFloat() <= 0.25F) {
                        const auto opposite = DirectionUtil::getOpposite(direction);
                        const auto blockpos = pos.add(DirectionUtil::getXOffset(opposite), 0, DirectionUtil::getZOffset(opposite));
                        if (Feature::isAirAt(reader, blockpos)) {
                            const auto state = Blocks::COCOA->getDefaultState()
                                    .set<CocoaBlock::AGE>(random.nextInt(3))
                                    .set<CocoaBlock::FACING>(direction);
                            TreeDecorator::placeBlock(reader, blockpos, state, positions3, boundingBox);
                        }
                    }
                }
            }
        }
    }
}

#include "TreeDecorator.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../util/math/utility.hpp"
#include "../../../util/math/BoundingBox.hpp"

void TreeDecorator::placeBlock(WorldWriter &writer, const BlockPos &pos, BlockData state, std::set<BlockPos> &positions, BoundingBox &boundingBox) {
    writer.setData(pos, state/*, 19*/);
    positions.emplace(pos);
    boundingBox.expandTo(BoundingBox::from(pos, pos));
}

void TreeDecorator::placeVine(WorldWriter &writer, const BlockPos &pos, Property property, std::set<BlockPos> &positions, BoundingBox &boundingBox) {
    placeBlock(writer, pos, Blocks::VINE->getDefaultState().set(property, true), positions, boundingBox);
}

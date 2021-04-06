#include "AbstractTrunkPlacer.hpp"
#include "../feature/TreeFeature.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../util/math/BoundingBox.hpp"
#include "../../../util/math/utility.hpp"

bool AbstractTrunkPlacer::isDirt(WorldReader &reader, const BlockPos &pos) {
    auto block = reader.getData(pos).getBlock();
    return block == Blocks::DIRT
        || block == Blocks::PODZOL
        || block == Blocks::COARSE_DIRT;
}

void AbstractTrunkPlacer::placeBlockState(WorldWriter &reader, const BlockPos &blockPos, BlockData state, BoundingBox &boundingBox) {
    TreeFeature::placeBlockState(reader, blockPos, state);
    boundingBox.expandTo(BoundingBox::from(blockPos, blockPos));
}

void AbstractTrunkPlacer::placeDirt(WorldGenRegion &reader, const BlockPos &blockPos) {
    if (!isDirt(reader, blockPos)) {
        TreeFeature::placeBlockState(reader, blockPos, Blocks::DIRT->getDefaultState());
    }
}

bool AbstractTrunkPlacer::placeTrunk(WorldGenRegion &reader, Random &random, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    if (TreeFeature::isReplaceableAt(reader, pos)) {
        placeBlockState(reader, pos, config.trunkProvider->getBlockState(random, pos), boundingBox);
        set1.emplace(pos);
        return true;
    }
    return false;
}

void AbstractTrunkPlacer::tryPlaceTrunk(WorldGenRegion &reader, Random &random, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) {
    if (TreeFeature::isReplaceableOrLogAt(reader, pos)) {
        placeTrunk(reader, random, pos, set1, boundingBox, config);
    }
}

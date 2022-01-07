#include "NetherackBlobReplacementStructure.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool NetherackBlobReplacementStructure::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto &cfg = std::get<BlobReplacementConfig>(config);

    const auto block = cfg.target.getBlock();
    const auto start = getLowestPosition(reader, pos.clampAxisCoordinate(DirectionAxis::Y, 1, /*reader.getHeight()*/ 256 - 1).value(), block);
    if (!start.has_value()) {
        return false;
    }
    const auto radius = cfg.radius.get(random);
    auto flag = false;

//    for (const auto blockpos : BlockPos::getProximitySortedBoxPositions(start, radius, radius, radius)) {
//        if (blockpos.manhattanDistance(start) > radius) {
//            break;
//        }
//
//        const auto state = reader.getData(blockpos);
//        if (state.is(block)) {
//            setBlockState(reader, blockpos, cfg.state);
//            flag = true;
//        }
//    }
    return flag;
}

auto NetherackBlobReplacementStructure::getLowestPosition(WorldGenRegion &reader, const BlockPos &start, Block *block) -> tl::optional<BlockPos> {
    for (auto pos = start; pos.y > 1; pos = pos.down()) {
        if (reader.getData(pos).is(block)) {
            return pos;
        }
    }
    return tl::nullopt;
}

#include "WorldGenRegion.hpp"
#include "world/chunk/Chunk.hpp"
#include "world/ServerWorld.hpp"
#include "block/Block.hpp"

auto WorldGenRegion::getBlock(int32_t x, int32_t y, int32_t z) const -> Block * {
    return Block::id_to_block[(int) getData(x, y, z).id];
}

auto WorldGenRegion::getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
    if (y < 0 || y > 255) {
        return {};
    }
    return getChunk(x >> 4, z >> 4)->getData(x, y, z);
}

void WorldGenRegion::setData(int32_t x, int32_t y, int32_t z, BlockData blockData) {
    getChunk(x >> 4, z >> 4)->setData(x, y, z, blockData);
}

void WorldGenRegion::setLight(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val) {
    getChunk(x >> 4, z >> 4)->setLight(x, y, z, channel, val);
}

auto WorldGenRegion::getLight(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t {
    return getChunk(x >> 4, z >> 4)->getLight(x, y, z, channel);
}

auto WorldGenRegion::getLightPacked(int32_t x, int32_t y, int32_t z) const -> int32_t {
    return getChunk(x >> 4, z >> 4)->getLightPacked(x, y, z);
}

auto WorldGenRegion::getTopBlockY(int32_t x, int32_t z) -> int32_t {
    return getChunk(x >> 4, z >> 4)->getTopBlockY(x, z);
}

auto WorldGenRegion::getHeight(int32_t x, int32_t z) -> int32_t {
    return getChunk(x >> 4, z >> 4)->getHeight(x, z);
}

Biome *WorldGenRegion::getNoiseBiomeRaw(int x, int y, int z) {
    return world->getNoiseBiomeRaw(x, y, z);
}

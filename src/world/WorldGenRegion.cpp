#include "WorldGenRegion.hpp"
#include "ServerWorld.hpp"
#include "chunk/Chunk.hpp"

auto WorldGenRegion::getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
    return getData(x, y, z).getBlock();
}

auto WorldGenRegion::getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
    if (y < 0 || y > 255) {
        return {};
    }
    return getChunk(x >> 4, z >> 4)->getData(x, y, z);
}

void WorldGenRegion::setData(int32_t x, int32_t y, int32_t z, BlockData blockData) {
    if (y < 0 || y > 255) {
        return;
    }

    getChunk(x >> 4, z >> 4)->setData(x, y, z, blockData);
}

void WorldGenRegion::setLightFor(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val) {
    if (y < 0 || y > 255) {
        return;
    }

    getChunk(x >> 4, z >> 4)->setLight(x, y, z, channel, val);
}

auto WorldGenRegion::getLightFor(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t {
    if (y < 0 || y > 255) {
        return 0;
    }
    return getChunk(x >> 4, z >> 4)->getLight(x, y, z, channel);
}

auto WorldGenRegion::getLightPacked(int32_t x, int32_t y, int32_t z) const -> int32_t {
    if (y < 0 || y > 255) {
        return 0;
    }
    return getChunk(x >> 4, z >> 4)->getLightPacked(x, y, z);
}

//auto WorldGenRegion::getTopBlockY(int32_t x, int32_t z) -> int32_t {
//    return getChunk(x >> 4, z >> 4)->getTopBlockY(x, z);
//}
//
//auto WorldGenRegion::getHeight(int32_t x, int32_t z) -> int32_t {
//    return getChunk(x >> 4, z >> 4)->getHeight(x, z);
//}

Biome *WorldGenRegion::getNoiseBiomeRaw(int x, int y, int z) {
    return world->getNoiseBiomeRaw(x, y, z);
}
int WorldGenRegion::getHeight(HeightmapType type, int x, int z) {
    return getChunk(x >> 4, z >> 4)->getHeight(type, x & 15, z & 15);
}
int32_t WorldGenRegion::getBlockLight(const glm::ivec3& pos) const {
    return getLightFor(pos, 0);
}

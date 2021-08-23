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

bool WorldGenRegion::setData(int32_t x, int32_t y, int32_t z, BlockData data) {
    if (y < 0 || y > 255) {
        return false;
    }

    return getChunk(x >> 4, z >> 4)->setData(x, y, z, data);
}

void WorldGenRegion::setLightFor(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val) {
    static constexpr std::array setLight {
        &Chunk::setSkyLight,
        &Chunk::setBlockLight,
    };
    (getChunk(x >> 4, z >> 4)->*setLight[channel])(x, y, z, val);
}

auto WorldGenRegion::getLightFor(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t {
    static constexpr std::array getLight {
        &Chunk::getSkyLight,
        &Chunk::getBlockLight,
    };
    return (getChunk(x >> 4, z >> 4)->*getLight[channel])(x, y, z);
}

Biome *WorldGenRegion::getNoiseBiomeRaw(int x, int y, int z) {
    return world->getNoiseBiomeRaw(x, y, z);
}
auto WorldGenRegion::getHeight(HeightmapType type, int x, int z) -> int {
    return getChunk(x >> 4, z >> 4)->getHeight(type, x & 15, z & 15);
}
int32_t WorldGenRegion::getBlockLight(const BlockPos& pos) const {
    return getLightFor(pos, 0);
}

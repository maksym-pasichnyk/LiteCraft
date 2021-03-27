#include "WorldCarver.hpp"

#include "../../chunk/Chunk.hpp"
#include "../../biome/Biome.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"

static int MathHelper_floor(double value) {
    int i = static_cast<int>(value);
    return value < (double)i ? i - 1 : i;
}

WorldCarver::WorldCarver(int32_t maxHeight) : maxHeight{maxHeight} {
    carvableBlocks = {
        Blocks::STONE,
//        Blocks2::GRANITE,
//        Blocks2::DIORITE,
//        Blocks2::ANDESITE,
        Blocks::DIRT,
//        Blocks2::COARSE_DIRT,
        Blocks::PODZOL,
        Blocks::GRASS,
//        Blocks2::TERRACOTTA,
//        Blocks2::WHITE_TERRACOTTA,
//        Blocks2::ORANGE_TERRACOTTA,
//        Blocks2::MAGENTA_TERRACOTTA,
//        Blocks2::LIGHT_BLUE_TERRACOTTA,
//        Blocks2::YELLOW_TERRACOTTA,
//        Blocks2::LIME_TERRACOTTA,
//        Blocks2::PINK_TERRACOTTA,
//        Blocks2::GRAY_TERRACOTTA,
//        Blocks2::LIGHT_GRAY_TERRACOTTA,
//        Blocks2::CYAN_TERRACOTTA,
//        Blocks2::PURPLE_TERRACOTTA,
//        Blocks2::BLUE_TERRACOTTA,
//        Blocks2::BROWN_TERRACOTTA,
//        Blocks2::GREEN_TERRACOTTA,
//        Blocks2::RED_TERRACOTTA,
//        Blocks2::BLACK_TERRACOTTA,
        Blocks::SANDSTONE,
        Blocks::RED_SANDSTONE,
        Blocks::MYCELIUM,
        Blocks::SNOW,
        Blocks::PACKED_ICE
    };
    carvableFluids = {
        Blocks::WATER
    };
}

bool WorldCarver::canCarveBlock(const BlockData &data, const BlockData &above) {
    return carvableBlocks.contains(data.getBlock())
        || (data.isIn(Blocks::SAND) || data.isIn(Blocks::GRAVEL))
        && !above.isIn(Blocks::WATER);// && !above.getFluidState().isTagged(FluidTags.WATER);
}

bool WorldCarver::carveBlocks(Chunk &chunk, const BiomeReadFn &getBiome, int64_t seed, int seaLevel, int chunkx, int chunkz, double xcoord, double ycoord, double zcoord, double unk1, double unk2/*, BitSet carvingMask*/) {
    auto random = Random::from(seed + static_cast<int64_t>(chunkx) + static_cast<int64_t>(chunkz));
    double d0 = chunkx * 16 + 8;
    double d1 = chunkz * 16 + 8;

    if ((xcoord < (d0 - 16.0 - unk1 * 2.0)) ||
        (zcoord < (d1 - 16.0 - unk1 * 2.0)) ||
        (xcoord > (d0 + 16.0 + unk1 * 2.0)) ||
        (zcoord > (d1 + 16.0 + unk1 * 2.0))) {
        return false;
    }
    const int minX = std::max(MathHelper_floor(xcoord - unk1) - chunkx * 16 - 1, 0);
    const int maxX = std::min(MathHelper_floor(xcoord + unk1) - chunkx * 16 + 1, 16);
    const int minY = std::max(MathHelper_floor(ycoord - unk2) - 1, 1);
    const int maxY = std::min(MathHelper_floor(ycoord + unk2) + 1, maxHeight - 8);
    const int minZ = std::max(MathHelper_floor(zcoord - unk1) - chunkz * 16 - 1, 0);
    const int maxZ = std::min(MathHelper_floor(zcoord + unk1) - chunkz * 16 + 1, 16);

    if (hasCarvableFluids(chunk, chunkx, chunkz, minX, maxX, minY, maxY, minZ, maxZ)) {
        return false;
    }
    bool flag = false;

    for (int x = minX; x < maxX; ++x) {
        const int xStart = x + chunkx * 16;
        const double d2 = (static_cast<double>(xStart) + 0.5 - xcoord) / unk1;

        for (int z = minZ; z < maxZ; ++z) {
            const int zStart = z + chunkz * 16;
            const double d3 = (static_cast<double>(zStart) + 0.5 - zcoord) / unk1;
            if (d2 * d2 + d3 * d3 >= 1.0) {
                continue;
            }
            bool isSurface = false;
            for (int y = maxY; y > minY; --y) {
                const double d4 = (static_cast<double>(y) - 0.5 - ycoord) / unk2;
                if (!shouldCarveBlock(d2, d4, d3, y)) {
                    flag |= carveBlock(chunk, getBiome, /*carvingMask,*/ random, seaLevel, chunkx, chunkz, xStart, zStart, x, y, z, isSurface);
                }
            }
        }
    }

    return flag;
}

bool WorldCarver::carveBlock(Chunk& chunk, const BiomeReadFn& getBiome, /*BitSet carvingMask,*/ Random& rand, int seaLevel, int chunkX, int chunkZ, int posX, int posZ, int x, int posY, int z, bool& isSurface) {
//    int i = x | z << 4 | posY << 8;
//    if (carvingMask.get(i)) {
//        return false;
//    }
//    carvingMask.set(i);
    const auto data = chunk.getData(posX, posY, posZ);
    if (data.isIn(Blocks::GRASS_BLOCK) || data.isIn(Blocks::MYCELIUM)) {
        isSurface = true;
    }
    const auto above = chunk.getData(posX, posY + 1, posZ);

    if (!canCarveBlock(data, above)) {
        return false;
    }
    if (posY < 11) {
        chunk.setData(posX, posY, posZ, Blocks::LAVA->getDefaultState()/*, false*/);
    } else {
        chunk.setData(posX, posY, posZ, Blocks::AIR->getDefaultState()/*, false*/);

        if (isSurface) {
            if (chunk.getData(posX, posY - 1, posZ).isIn(Blocks::DIRT)) {
                const auto top = getBiome({posX, posY, posZ})->biomeGenerationSettings.surfaceBuilder.config.top;
                chunk.setData(posX, posY - 1, posZ, top/*, false*/);
            }
        }
    }

    return true;
}

bool WorldCarver::hasCarvableFluids(Chunk &chunk, int chunkX, int chunkZ, int minX, int maxX, int minY, int maxY, int minZ, int maxZ) {
    for (int x = minX; x < maxX; ++x) {
        for (int z = minZ; z < maxZ; ++z) {
            for (int k = minY - 1; k <= maxY + 1; ++k) {
                if (carvableFluids.contains(chunk.getBlock(x + chunkX * 16, k, z + chunkZ * 16))) {
                    return true;
                }
//                if (carvableFluids.contains(chunk.getFluidState(x + chunkX * 16, k, z + chunkZ * 16).getFluid())) {
//                    return true;
//                }
                if (k != maxY + 1 && !isOnEdge(minX, maxX, minZ, maxZ, x, z)) {
                    k = maxY;
                }
            }
        }
    }

    return false;
}

bool WorldCarver::isInsideCarveRadius(int chunkx, int chunkz, double xcoord, double zcoord, int yoffset, int ycoord, float radius) {
    const double xoffset = chunkx * 16 + 8;
    const double zoffset = chunkz * 16 + 8;
    const double dx = xcoord - xoffset;
    const double dy = zcoord - zoffset;
    const double dz = ycoord - yoffset;
    const double rr = radius + 2.0F + 16.0F;
    return (dx * dx + dy * dy - dz * dz) <= (rr * rr);
}

bool WorldCarver::isOnEdge(int minX, int maxX, int minZ, int maxZ, int x, int z) {
    return x == minX || x == maxX - 1 || z == minZ || z == maxZ - 1;
}

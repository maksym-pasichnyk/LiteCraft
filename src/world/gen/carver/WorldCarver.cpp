#include "WorldCarver.hpp"

#include "../../chunk/Chunk.hpp"
#include "../../biome/Biome.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <block/States.hpp>

static int MathHelper_floor(double value) {
    int i = static_cast<int>(value);
    return value < (double)i ? i - 1 : i;
}

WorldCarver::WorldCarver(int32_t maxHeight) : maxHeight{maxHeight} {
    carvableBlocks = {
        Blocks::STONE,
        Blocks::GRANITE,
        Blocks::DIORITE,
        Blocks::ANDESITE,
        Blocks::DIRT,
        Blocks::COARSE_DIRT,
        Blocks::PODZOL,
        Blocks::GRASS,
        Blocks::TERRACOTTA,
        Blocks::WHITE_TERRACOTTA,
        Blocks::ORANGE_TERRACOTTA,
        Blocks::MAGENTA_TERRACOTTA,
        Blocks::LIGHT_BLUE_TERRACOTTA,
        Blocks::YELLOW_TERRACOTTA,
        Blocks::LIME_TERRACOTTA,
        Blocks::PINK_TERRACOTTA,
        Blocks::GRAY_TERRACOTTA,
        Blocks::LIGHT_GRAY_TERRACOTTA,
        Blocks::CYAN_TERRACOTTA,
        Blocks::PURPLE_TERRACOTTA,
        Blocks::BLUE_TERRACOTTA,
        Blocks::BROWN_TERRACOTTA,
        Blocks::GREEN_TERRACOTTA,
        Blocks::RED_TERRACOTTA,
        Blocks::BLACK_TERRACOTTA,
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
        || (data.is(Blocks::SAND) || data.is(Blocks::GRAVEL))
        && !above.is(Blocks::WATER);// && !above.getFluidState().isTagged(FluidTags.WATER);
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
    const int xmin = std::max(MathHelper_floor(xcoord - unk1) - chunkx * 16 - 1, 0);
    const int xmax = std::min(MathHelper_floor(xcoord + unk1) - chunkx * 16 + 1, 16);
    const int ymin = std::max(MathHelper_floor(ycoord - unk2) - 1, 1);
    const int ymax = std::min(MathHelper_floor(ycoord + unk2) + 1, maxHeight - 8);
    const int zmin = std::max(MathHelper_floor(zcoord - unk1) - chunkz * 16 - 1, 0);
    const int zmax = std::min(MathHelper_floor(zcoord + unk1) - chunkz * 16 + 1, 16);

    if (hasCarvableFluids(chunk, chunkx, chunkz, xmin, xmax, ymin, ymax, zmin, zmax)) {
        return false;
    }
    bool flag = false;

    for (int x = xmin; x < xmax; ++x) {
        const int xpos = x + (chunkx << 4);
        const double d2 = (static_cast<double>(xpos) + 0.5 - xcoord) / unk1;

        for (int z = zmin; z < zmax; ++z) {
            const int zpos = z + chunkz * 16;
            const double d3 = (static_cast<double>(zpos) + 0.5 - zcoord) / unk1;
            if (d2 * d2 + d3 * d3 >= 1.0) {
                continue;
            }
            bool is_surface = false;
            for (int y = ymax; y > ymin; --y) {
                const auto i = x | (z << 4) | (y << 8);

                if (!chunk.carvingMask.test(i)) {
                    const double d4 = (static_cast<double>(y) - 0.5 - ycoord) / unk2;
                    if (!isOutsideCaveRadius(d2, d4, d3, y)) {
                        chunk.carvingMask.set(i, true);

                        if (carveBlock(chunk, getBiome, random, seaLevel, chunkx, chunkz, xpos, y, zpos, is_surface)) {
                            flag = true;
                        }
                    }
                }
            }
        }
    }

    return flag;
}

bool WorldCarver::carveBlock(Chunk& chunk, const BiomeReadFn& getBiome, Random& rand, int seaLevel, int chunkX, int chunkZ, int xpos, int ypos, int zpos, bool& is_surface) {
    const auto data = chunk.getData(xpos, ypos, zpos);
    if (data.is(Blocks::GRASS_BLOCK) || data.is(Blocks::MYCELIUM)) {
        is_surface = true;
    }
    const auto above = chunk.getData(xpos, ypos + 1, zpos);

    if (!canCarveBlock(data, above)) {
        return false;
    }
    if (ypos < 11) {
        chunk.setData(xpos, ypos, zpos, States::LAVA/*, false*/);
    } else {
        chunk.setData(xpos, ypos, zpos, States::AIR/*, false*/);

        if (is_surface) {
            if (chunk.getData(xpos, ypos - 1, zpos).is(Blocks::DIRT)) {
                const auto top = getBiome({xpos, ypos, zpos})-> biomeGenerationSettings.getSurfaceBuilderConfig().getTop();
                chunk.setData(xpos, ypos - 1, zpos, top/*, false*/);
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

#include "StructurePiece.hpp"
#include "../../../WorldReader.hpp"
#include "../../../WorldGenRegion.hpp"
#include "../../../../block/Block.hpp"
#include "../../../../block/Blocks.hpp"
#include <spdlog/spdlog.h>

BlockData StructurePiece::getBlockStateFromPos(WorldReader &reader, int x, int y, int z, const BoundingBox &bb) const {
    const auto pos = getRelativePosition(x, y, z);
    return !bb.isVecInside(pos) ? Blocks::AIR->getDefaultState() : reader.getData(pos);
}

bool StructurePiece::isLiquidInStructureBoundingBox(WorldReader &reader, const BoundingBox &bb) const {
    const auto xmin = std::max(bounds.minX - 1, bb.minX);
    const auto ymin = std::max(bounds.minY - 1, bb.minY);
    const auto zmin = std::max(bounds.minZ - 1, bb.minZ);
    const auto xmax = std::min(bounds.maxX + 1, bb.maxX);
    const auto ymax = std::min(bounds.maxY + 1, bb.maxY);
    const auto zmax = std::min(bounds.maxZ + 1, bb.maxZ);

    for (int x = xmin; x <= xmax; ++x) {
        for (int z = zmin; z <= zmax; ++z) {
            if (reader.isLiquidBlock(BlockPos(x, ymin, z))) {
                return true;
            }

            if (reader.isLiquidBlock(BlockPos(x, ymax, z))) {
                return true;
            }
        }
    }

    for (int x = xmin; x <= xmax; ++x) {
        for (int y = ymin; y <= ymax; ++y) {
            if (reader.isLiquidBlock(BlockPos(x, y, zmin))) {
                return true;
            }

            if (reader.isLiquidBlock(BlockPos(x, y, zmax))) {
                return true;
            }
        }
    }

    for (int z = zmin; z <= zmax; ++z) {
        for (int y = ymin; y <= ymax; ++y) {
            if (reader.isLiquidBlock(BlockPos(xmin, y, z))) {
                return true;
            }

            if (reader.isLiquidBlock(BlockPos(xmax, y, z))) {
                return true;
            }
        }
    }

    return false;
}

bool StructurePiece::isUnderOceanFloor(WorldGenRegion &region, int x, int y, int z, const BoundingBox &bb) const {
    const auto pos = getRelativePosition(x, y + 1, z);
    if (!bb.isVecInside(pos)) {
        return false;
    }
    return pos.y < region.getHeight(HeightmapType::OCEAN_FLOOR_WG, pos).y;
}

void StructurePiece::fillWithAir(WorldGenRegion &region, const BoundingBox &bb, int minX, int minY, int minZ, int maxX, int maxY, int maxZ) const {
    const auto AIR = Blocks::AIR->getDefaultState();

    for (int i = minY; i <= maxY; ++i) {
        for (int j = minX; j <= maxX; ++j) {
            for (int k = minZ; k <= maxZ; ++k) {
                setBlockState(region, AIR, j, i, k, bb);
            }
        }
    }
}

void StructurePiece::fillWithBlocks(WorldGenRegion &region, const BoundingBox &bb, int xMin, int yMin, int zMin, int xMax, int yMax, int zMax, BlockData boundaryBlockState, BlockData insideBlockState, bool existingOnly) const {
    for (int y = yMin; y <= yMax; ++y) {
        for (int x = xMin; x <= xMax; ++x) {
            for (int z = zMin; z <= zMax; ++z) {
                if (!existingOnly || !getBlockStateFromPos(region, x, y, z, bb).isAir()) {
                    if (y != yMin && y != yMax && x != xMin && x != xMax && z != zMin && z != zMax) {
                        setBlockState(region, insideBlockState, x, y, z, bb);
                    } else {
                        setBlockState(region, boundaryBlockState, x, y, z, bb);
                    }
                }
            }
        }
    }
}

void StructurePiece::fillWithRandomizedBlocks(WorldGenRegion &region, const BoundingBox &bb, int minX, int minY, int minZ, int maxX, int maxY, int maxZ, bool alwaysReplace, Random &random, BlockSelector &selector) const {
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            for (int z = minZ; z <= maxZ; ++z) {
                if (!alwaysReplace || !getBlockStateFromPos(region, x, y, z, bb).isAir()) {
                    const auto state = selector.select(random, x, y, z, y == minY || y == maxY || x == minX || x == maxX || z == minZ || z == maxZ);
                    setBlockState(region, state, x, y, z, bb);
                }
            }
        }
    }
}

void StructurePiece::generateMaybeBox(WorldGenRegion &region, const BoundingBox &bb, Random &random, float chance, int x1, int y1, int z1, int x2, int y2, int z2, BlockData edgeState, BlockData state, bool requireNonAir, bool requiredSkylight) const {
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            for (int z = z1; z <= z2; ++z) {
                if (random.nextFloat() > chance) continue;
                if (requireNonAir && getBlockStateFromPos(region, x, y, z, bb).isAir()) continue;
                if (requiredSkylight && !isUnderOceanFloor(region, x, y, z, bb)) continue;

                if (y != y1 && y != y2 && x != x1 && x != x2 && z != z1 && z != z2) {
                    setBlockState(region, state, x, y, z, bb);
                } else {
                    setBlockState(region, edgeState, x, y, z, bb);
                }
            }
        }
    }
}

void StructurePiece::setBlockState(WorldGenRegion &region, BlockData state, int x, int y, int z, const BoundingBox &bb) const {
    const auto pos = getRelativePosition(x, y, z);
    if (bb.isVecInside(pos)) {
        state = state.mirror(mirror).rotate(rotation);

        region.setData(pos, state/*, 2*/);
//        FluidState fluidstate = region.getFluidState(pos);
//        if (!fluidstate.isEmpty()) {
//            region.getPendingFluidTicks().scheduleTick(pos, fluidstate.getFluid(), 0);
//        }

//        if (BLOCKS_NEEDING_POSTPROCESSING.contains(state.getBlock())) {
//            region.getChunk(pos).markBlockForPostprocessing(pos);
//        }
    }
}

void StructurePiece::replaceAirAndLiquidDownwards(WorldGenRegion& region, BlockData state, int x, int y, int z, const BoundingBox& bb) const {
    auto pos = getRelativePosition(x, y, z);
    if (bb.isVecInside(pos)) {
        while (pos.y > 1 && (region.isAirBlock(pos) || region.getData(pos).getMaterial()->isLiquid)) {
            region.setData(pos, state/*, 2*/);
            pos = pos.down();
        }
    }
}

void StructurePiece::randomlyRareFillWithBlocks(WorldGenRegion &region, const BoundingBox &bb, int minX, int minY, int minZ, int maxX, int maxY, int maxZ, BlockData state, bool excludeAir) const {
    const auto f0 = static_cast<float>(maxX - minX + 1);
    const auto f1 = static_cast<float>(maxY - minY + 1);
    const auto f2 = static_cast<float>(maxZ - minZ + 1);
    const auto f3 = static_cast<float>(minX) + f0 * 0.5F;
    const auto f4 = static_cast<float>(minZ) + f2 * 0.5F;

    for (int i = minY; i <= maxY; ++i) {
        const auto f5 = static_cast<float>(i - minY) / f1;

        for (int j = minX; j <= maxX; ++j) {
            const auto f6 = (static_cast<float>(j) - f3) / (f0 * 0.5F);

            for (int k = minZ; k <= maxZ; ++k) {
                const auto f7 = (static_cast<float>(k) - f4) / (f2 * 0.5F);
                if (!excludeAir || !getBlockStateFromPos(region, j, i, k, bb).isAir()) {
                    const auto f8 = f6 * f6 + f5 * f5 + f7 * f7;
                    if (f8 <= 1.05F) {
                        setBlockState(region, state, j, i, k, bb);
                    }
                }
            }
        }
    }
}

void StructurePiece::randomlyPlaceBlock(WorldGenRegion &region, const BoundingBox &bb, Random& random, float chance, int x, int y, int z, BlockData state) const {
    if (random.nextFloat() < chance) {
        setBlockState(region, state, x, y, z, bb);
    }
}
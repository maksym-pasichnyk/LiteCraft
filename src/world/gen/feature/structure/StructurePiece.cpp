#include "StructurePiece.hpp"
#include "../../../WorldReader.hpp"
#include "../../../WorldGenRegion.hpp"
#include "../../../../block/Block.hpp"
#include "../../../../block/Blocks.hpp"

BlockData StructurePiece::getBlockStateFromPos(WorldReader &reader, int x, int y, int z, const BoundingBox &bb) const {
    const auto pos = BlockPos::from(getXWithOffset(x, z), getYWithOffset(y), getZWithOffset(x, z));
    return !bb.isVecInside(pos) ? Blocks::AIR->getDefaultState() : reader.getData(pos);
}

bool StructurePiece::isLiquidInStructureBoundingBox(WorldReader &reader, const BoundingBox &bb) const {
    const int xmin = std::max(bounds.minX - 1, bb.minX);
    const int ymin = std::max(bounds.minY - 1, bb.minY);
    const int zmin = std::max(bounds.minZ - 1, bb.minZ);
    const int xmax = std::min(bounds.maxX + 1, bb.maxX);
    const int ymax = std::min(bounds.maxY + 1, bb.maxY);
    const int zmax = std::min(bounds.maxZ + 1, bb.maxZ);

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
    const int i = getXWithOffset(x, z);
    const int j = getYWithOffset(y + 1);
    const int k = getZWithOffset(x, z);
    if (!bb.contains(i, j, k)) {
        return false;
    }
    return j < region.getHeight(HeightmapType::OCEAN_FLOOR_WG, i, k);
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
//                    selector.selectBlocks(random, x, y, z, y == minY || y == maxY || x == minX || x == maxX || z == minZ || z == maxZ);
//                    setBlockState(region, selector.getBlockState(), x, y, z, bb);
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
    const auto pos = BlockPos(getXWithOffset(x, z), getYWithOffset(y), getZWithOffset(x, z));
    if (bb.isVecInside(pos)) {
//        if (mirror != Mirror::NONE) {
//            state = state.mirror(mirror);
//        }
//
//        if (rotation != Rotation::NONE) {
//            state = state.rotate(rotation);
//        }

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

void StructurePiece::randomlyRareFillWithBlocks(WorldGenRegion &region, const BoundingBox &bb, int minX, int minY, int minZ, int maxX, int maxY, int maxZ, BlockData state, bool excludeAir) const {
    const float f0 = static_cast<float>(maxX - minX + 1);
    const float f1 = static_cast<float>(maxY - minY + 1);
    const float f2 = static_cast<float>(maxZ - minZ + 1);
    const float f3 = static_cast<float>(minX) + f0 / 2.0F;
    const float f4 = static_cast<float>(minZ) + f2 / 2.0F;

    for (int i = minY; i <= maxY; ++i) {
        const float f5 = static_cast<float>(i - minY) / f1;

        for (int j = minX; j <= maxX; ++j) {
            const float f6 = (static_cast<float>(j) - f3) / (f0 * 0.5F);

            for (int k = minZ; k <= maxZ; ++k) {
                const float f7 = (static_cast<float>(k) - f4) / (f2 * 0.5F);
                if (!excludeAir || !getBlockStateFromPos(region, j, i, k, bb).isAir()) {
                    const float f8 = f6 * f6 + f5 * f5 + f7 * f7;
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
#pragma once

#include <cmath>
#include <type_traits>
#include <glm/vec3.hpp>
#include <util/math/BlockPos.hpp>

struct BoundingBox {
    static constexpr auto from(const BlockPos& pos) -> BoundingBox {
        return BoundingBox{
            .minX = pos.x,
            .minY = pos.y,
            .minZ = pos.z,
            .maxX = pos.x,
            .maxY = pos.y,
            .maxZ = pos.z
        };
    }

    static constexpr auto from(const BlockPos& from, const BlockPos& to) -> BoundingBox {
        return BoundingBox{
            .minX = std::min(from.x, to.x),
            .minY = std::min(from.y, to.y),
            .minZ = std::min(from.z, to.z),
            .maxX = std::max(from.x, to.x),
            .maxY = std::max(from.y, to.y),
            .maxZ = std::max(from.z, to.z)
        };
    }
    
    static constexpr auto withSize(int x, int y, int z, int size_x, int size_y, int size_z) -> BoundingBox {
        return BoundingBox{
            .minX = x,
            .minY = y,
            .minZ = z,
            .maxX = x + size_x - 1,
            .maxY = y + size_y - 1,
            .maxZ = z + size_z - 1
        };
    }

    static constexpr auto fromChunkPos(int chunk_x, int chunk_z) -> BoundingBox {
        const auto pos_x = chunk_x << 4;
        const auto pos_z = chunk_z << 4;

        return BoundingBox{
            .minX = pos_x,
            .minY = 0,
            .minZ = pos_z,
            .maxX = pos_x + 15,
            .maxY = 255,
            .maxZ = pos_z + 15
        };
    }

    static constexpr auto getNewBoundingBox() -> BoundingBox {
        return BoundingBox{
            .minX = std::numeric_limits<int>::max(),
            .minY = std::numeric_limits<int>::max(),
            .minZ = std::numeric_limits<int>::max(),
            .maxX = std::numeric_limits<int>::min(),
            .maxY = std::numeric_limits<int>::min(),
            .maxZ = std::numeric_limits<int>::min()
        };
    }

    static constexpr auto newInfinityBoundingBox() -> BoundingBox {
        return BoundingBox{
            .minX = std::numeric_limits<int>::min(),
            .minY = std::numeric_limits<int>::min(),
            .minZ = std::numeric_limits<int>::min(),
            .maxX = std::numeric_limits<int>::max(),
            .maxY = std::numeric_limits<int>::max(),
            .maxZ = std::numeric_limits<int>::max()
        };
    }
    
    int minX;
    int minY;
    int minZ;
    int maxX;
    int maxY;
    int maxZ;

    constexpr void offset(int x, int y, int z) {
        minX += x;
        minY += y;
        minZ += z;
        maxX += x;
        maxY += y;
        maxZ += z;
    }

    constexpr auto contains(int x, int y, int z) const noexcept -> bool {
        return minX <= x && x <= maxX &&
               minY <= y && y <= maxY &&
               minZ <= z && z <= maxZ;
    }

    constexpr auto intersectsWith(const BoundingBox& boundingBox) const noexcept -> bool {
        return minX <= boundingBox.maxX && maxX >= boundingBox.minX &&
               minY <= boundingBox.maxY && maxY >= boundingBox.minY &&
               minZ <= boundingBox.maxZ && maxZ >= boundingBox.minZ;
    }

    constexpr void expandTo(const BoundingBox& boundingBox) noexcept {
        minX = std::min(minX, boundingBox.minX);
        minY = std::min(minY, boundingBox.minY);
        minZ = std::min(minZ, boundingBox.minZ);
        maxX = std::max(maxX, boundingBox.maxX);
        maxY = std::max(maxY, boundingBox.maxY);
        maxZ = std::max(maxZ, boundingBox.maxZ);
    }
    
    constexpr auto isVecInside(const BlockPos& pos) const noexcept -> bool {
        return contains(pos.x, pos.y, pos.z);
    }

    constexpr auto getXSize() const noexcept -> int {
        return maxX - minX + 1;
    }

    constexpr auto getYSize() const noexcept -> int {
        return maxY - minY + 1;
    }

    constexpr auto getZSize() const noexcept -> int {
        return maxZ - minZ + 1;
    }

    constexpr auto getSize() const noexcept -> BlockPos {
        return BlockPos::from(getXSize(), getYSize(), getZSize());
    }

    constexpr auto getPivotCenter() const noexcept -> BlockPos {
        return BlockPos::from(minX, minY, minZ) + getSize() / 2;
    }

    static auto getComponentToAddBoundingBox(int structureMinX, int structureMinY, int structureMinZ, int xMin, int yMin, int zMin, int xMax, int yMax, int zMax, Direction facing) -> BoundingBox {
        switch (facing) {
            case Direction::NORTH:
                return BoundingBox{structureMinX + xMin, structureMinY + yMin, structureMinZ - zMax + 1 + zMin, structureMinX + xMax - 1 + xMin, structureMinY + yMax - 1 + yMin, structureMinZ + zMin};
            case Direction::SOUTH:
                return BoundingBox{structureMinX + xMin, structureMinY + yMin, structureMinZ + zMin, structureMinX + xMax - 1 + xMin, structureMinY + yMax - 1 + yMin, structureMinZ + zMax - 1 + zMin};
            case Direction::WEST:
                return BoundingBox{structureMinX - zMax + 1 + zMin, structureMinY + yMin, structureMinZ + xMin, structureMinX + zMin, structureMinY + yMax - 1 + yMin, structureMinZ + xMax - 1 + xMin};
            case Direction::EAST:
                return BoundingBox{structureMinX + zMin, structureMinY + yMin, structureMinZ + xMin, structureMinX + zMax - 1 + zMin, structureMinY + yMax - 1 + yMin, structureMinZ + xMax - 1 + xMin};
            default:
                return BoundingBox{structureMinX + xMin, structureMinY + yMin, structureMinZ + zMin, structureMinX + xMax - 1 + xMin, structureMinY + yMax - 1 + yMin, structureMinZ + zMax - 1 + zMin};
        }
    }
};
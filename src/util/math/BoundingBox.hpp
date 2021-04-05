#pragma once

#include <type_traits>

struct BoundingBox {
    static constexpr BoundingBox from(const glm::ivec3& vec1, const glm::ivec3& vec2) {
        return {
            .minX = std::min(vec1.x, vec2.x),
            .minY = std::min(vec1.y, vec2.y),
            .minZ = std::min(vec1.z, vec2.z),
            .maxX = std::max(vec1.x, vec2.x),
            .maxY = std::max(vec1.y, vec2.y),
            .maxZ = std::max(vec1.z, vec2.z)
        };
    }
    
    static constexpr BoundingBox withSize(int x, int y, int z, int size_x, int size_y, int size_z) {
        return BoundingBox{
            .minX = x,
            .minY = y,
            .minZ = z,
            .maxX = x + size_x - 1,
            .maxY = y + size_y - 1,
            .maxZ = z + size_z - 1
        };
    }

    static constexpr BoundingBox fromChunkPos(int chunk_x, int chunk_z) {
        const int pos_x = chunk_x << 4;
        const int pos_z = chunk_z << 4;

        return BoundingBox{
            .minX = pos_x,
            .minY = 0,
            .minZ = pos_z,
            .maxX = pos_x + 15,
            .maxY = 255,
            .maxZ = pos_z + 15
        };
    }

    static constexpr BoundingBox getNewBoundingBox() {
        return BoundingBox{
            .minX = std::numeric_limits<int>::max(),
            .minY = std::numeric_limits<int>::max(),
            .minZ = std::numeric_limits<int>::max(),
            .maxX = std::numeric_limits<int>::min(),
            .maxY = std::numeric_limits<int>::min(),
            .maxZ = std::numeric_limits<int>::min()
        };
    }

    static constexpr BoundingBox newInfinityBoundingBox() {
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

    constexpr bool contains(int x, int y, int z) const noexcept {
        return minX <= x && x <= maxX &&
               minY <= y && y <= maxY &&
               minZ <= z && z <= maxZ;
    }

    constexpr bool intersect(const BoundingBox& boundingBox) const noexcept {
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
};
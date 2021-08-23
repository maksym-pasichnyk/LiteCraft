#pragma once

#include "StructurePiece.hpp"
#include <world/WorldGenRegion.hpp>

struct ScatteredStructurePiece : StructurePiece {
    int width;
    int height;
    int depth;
    int hPos = -1;

    ScatteredStructurePiece(Random& random, int x, int y, int z, int width, int height, int depth) : StructurePiece(0), width(width), height(height), depth(depth) {
        setCoordBaseMode(random.nextElement(std::span(DirectionUtil::Plane::HORIZONTAL)));

        if (DirectionUtil::getAxis(*coordBaseMode) == DirectionAxis::Z) {
            bounds = BoundingBox::withSize(x, y, z, width, height, depth);
        } else {
            bounds = BoundingBox::withSize(x, y, z, depth, height, width);
        }
    }

    bool isInsideBounds(HeightReader& reader, const BoundingBox& bb, int y_offset) {
        if (hPos >= 0) {
            return true;
        }

        int sum_height = 0;
        int count = 0;

        for (int z = bounds.minZ; z <= bounds.maxZ; ++z) {
            for (int x = bounds.minX; x <= bounds.maxX; ++x) {
                const auto pos = BlockPos::from(x, 64, z);
                if (bb.isVecInside(pos)) {
                    sum_height += reader.getHeight(HeightmapType::MOTION_BLOCKING_NO_LEAVES, pos.x, pos.z);
                    ++count;
                }
            }
        }

        if (count == 0) {
            return false;
        }

        hPos = sum_height / count;
        bounds.offset(0, hPos - bounds.minY + y_offset, 0);
        return true;
    }
};
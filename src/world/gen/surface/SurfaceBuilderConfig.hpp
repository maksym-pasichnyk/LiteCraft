#pragma once

#include <block/BlockData.hpp>

struct SurfaceBuilderConfig {
    BlockData top;
    BlockData mid;
    BlockData underWater;

    auto getTop() const -> BlockData {
        return top;
    }

    auto getUnder() const -> BlockData {
        return mid;
    }

    auto getUnderWaterMaterial() const -> BlockData {
        return underWater;
    }
};
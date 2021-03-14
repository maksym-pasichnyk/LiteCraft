#pragma once

#include <tuple>
#include <queue>
#include <bitset>

#include "../../WorldGenRegion.hpp"
#include "../chunk/Chunk.hpp"

struct WorldLightManager {
    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t>> sources;
    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t>> removes;

    void remove(WorldGenRegion& region, int32_t x, int32_t y, int32_t z, int32_t channel, int32_t src_light, std::bitset<9>& mask) {
        const auto light = region.getLight(x, y, z, channel);

        if (light != 0 && light < src_light) {
            mask.set(region.toIndex(x >> 4, z >> 4), true);

            region.setLight(x, y, z, channel, 0);
            removes.emplace(x, y, z, channel, light);
        } else if (light >= src_light) {
            sources.emplace(x, y, z, channel);
        }
    }

    void propagate(WorldGenRegion& region, int32_t x, int32_t y, int32_t z, int32_t channel, int32_t src_light, std::bitset<9>& mask) {
        const auto light = region.getLight(x, y, z, channel);

        const auto new_light = src_light - 1;

        if (!isOpaque(region.getData(x, y, z)) && light < new_light) {
            mask.set(region.toIndex(x >> 4, z >> 4), true);

            region.setLight(x, y, z, channel, new_light);
            sources.emplace(x, y, z, channel);
        }
    }

    void proccess(WorldGenRegion& region, std::bitset<9>& mask) {
        while (!removes.empty()) {
            const auto [x, y, z, channel, light] = removes.front();
            removes.pop();

            remove(region, x + 1, y, z, channel, light, mask);
            remove(region, x - 1, y, z, channel, light, mask);

            remove(region, x, y, z - 1, channel, light, mask);
            remove(region, x, y, z + 1, channel, light, mask);

            remove(region, x, y + 1, z, channel, light, mask);
            remove(region, x, y - 1, z, channel, light, mask);
        }

        while (!sources.empty()) {
            const auto [x, y, z, channel] = sources.front();
            sources.pop();

            const auto light = region.getLight(x, y, z, channel);
            if (light <= 1) continue;

            propagate(region, x + 1, y, z, channel, light, mask);
            propagate(region, x - 1, y, z, channel, light, mask);

            propagate(region, x, y, z - 1, channel, light, mask);
            propagate(region, x, y, z + 1, channel, light, mask);

            propagate(region, x, y + 1, z, channel, light, mask);
            propagate(region, x, y - 1, z, channel, light, mask);
        }

        for (int i = 0; i < 9; i++) {
            if (mask.test(i)) {
                region.chunks[i]->needRender = true;
            }
        }
    }

    void column(WorldGenRegion& region, int32_t x, int32_t z) {
        int32_t y = 255;
        for (; y >= 0; --y) {
            if (isOpaque(region.getData(x, y, z))) {
                sources.emplace(x, y + 1, z, 3);
                break;
            }

            region.setLight(x, y, z, 3, 15);
        }

        for (; y >= 0; --y) {
//            removes.emplace(x, y, z, 0);

            sources.emplace(x + 1, y, z, 3);
            sources.emplace(x - 1, y, z, 3);

            sources.emplace(x, y, z - 1, 3);
            sources.emplace(x, y, z + 1, 3);

            sources.emplace(x, y + 1, z, 3);
            sources.emplace(x, y - 1, z, 3);

            region.setLight(x, y, z, 3, 0);
        }
    }

    void calculate(WorldGenRegion& region, int32_t xPos, int32_t zPos) {
        std::bitset<9> mask{};

        for (int32_t x = xPos; x < xPos + 16; x++) {
            for (int32_t z = zPos; z < zPos + 16; z++) {
                column(region, x, z);
            }
        }

        proccess(region, mask);
    }

    void update(WorldGenRegion& region, int32_t x, int32_t y, int32_t z, BlockData old, BlockData data) {
        std::bitset<9> mask{};

        if (isOpaque(data)) {
            removes.emplace(x, y, z, 3, region.getLight(x, y, z, 3));
            region.setLight(x, y, z, 3, 0);

            y -= 1;

            for (; y >= 0; --y) {
                removes.emplace(x, y, z, 3, region.getLight(x, y, z, 3));
                region.setLight(x, y, z, 3, 0);
            }
        } else {
//            removes.emplace(x, y, z, 0);

            for (int i = 0; i < 4; i++) {
                sources.emplace(x + 1, y, z, i);
                sources.emplace(x - 1, y, z, i);

                sources.emplace(x, y, z - 1, i);
                sources.emplace(x, y, z + 1, i);

                sources.emplace(x, y + 1, z, i);
                sources.emplace(x, y - 1, z, i);
            }
        }

        column(region, x, z);

        const auto bl_light = getLightFor(data);
        const auto light0 = region.getLight(x, y, z, 0);

        if (bl_light < light0) {
            removes.emplace(x, y, z, 0, light0);
        }
        region.setLight(x, y, z, 0, bl_light);

        if (bl_light > 0) {
            sources.emplace(x, y, z, 0);
        }

        proccess(region, mask);
    }
};

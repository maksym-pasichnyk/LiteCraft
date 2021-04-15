#pragma once

#include "../WorldGenRegion.hpp"
#include "../chunk/Chunk.hpp"
#include "../../block/Block.hpp"
#include "../../block/Blocks.hpp"

#include <tuple>
#include <queue>
#include <bitset>

struct WorldLightManager {
    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t>> sources;
    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t>> removes;

    void remove(WorldGenRegion& region, int32_t x, int32_t y, int32_t z, int32_t channel, int32_t src_light, std::bitset<9>& mask) {
        const auto light = region.getLightFor(x, y, z, channel);

        if (light != 0 && light < src_light) {
            mask.set(region.toIndex(x >> 4, z >> 4), true);

            region.setLightFor(x, y, z, channel, 0);
            removes.emplace(x, y, z, channel, light);
        } else if (light >= src_light) {
            sources.emplace(x, y, z, channel);
        }
    }

    void propagate(WorldGenRegion& region, int32_t x, int32_t y, int32_t z, int32_t channel, int32_t src_light, std::bitset<9>& mask) {
        const auto light = region.getLightFor(x, y, z, channel);

        const auto new_light = src_light - 1;

        const auto state = region.getData(x, y, z);
        if (!(/*state.isOpaque() &&*/ state.isSolid()) && light < new_light) {
            mask.set(region.toIndex(x >> 4, z >> 4), true);

            region.setLightFor(x, y, z, channel, new_light);
            sources.emplace(x, y, z, channel);
        }
    }

    void proccess(WorldGenRegion& region, std::bitset<9>& mask) {
        while (!removes.empty()) {
            const auto [x, y, z, channel, light] = removes.front();
            removes.pop();

            if (x < region.bounds_max.x) {
                remove(region, x + 1, y, z, channel, light, mask);
            }
            if (x > region.bounds_min.x) {
                remove(region, x - 1, y, z, channel, light, mask);
            }
            if (z > region.bounds_min.y) {
                remove(region, x, y, z - 1, channel, light, mask);
            }
            if (z < region.bounds_max.y) {
                remove(region, x, y, z + 1, channel, light, mask);
            }
            if (y < 255) {
                remove(region, x, y + 1, z, channel, light, mask);
            }
//            if (y > 0) {
                remove(region, x, y - 1, z, channel, light, mask);
//            }
        }

        while (!sources.empty()) {
            const auto [x, y, z, channel] = sources.front();
            sources.pop();

            const auto light = region.getLightFor(x, y, z, channel);
            if (light <= 1) continue;

            if (x < region.bounds_max.x) {
                propagate(region, x + 1, y, z, channel, light, mask);
            }
            if (x > region.bounds_min.x) {
                propagate(region, x - 1, y, z, channel, light, mask);
            }
            if (z > region.bounds_min.y) {
                propagate(region, x, y, z - 1, channel, light, mask);
            }
            if (z < region.bounds_max.y) {
                propagate(region, x, y, z + 1, channel, light, mask);
            }
            if (y < 255) {
                propagate(region, x, y + 1, z, channel, light, mask);
            }
//            if (y > 0) {
                propagate(region, x, y - 1, z, channel, light, mask);
//            }
        }

//        for (int i = 0; i < 9; i++) {
//            if (mask.test(i)) {
//                region.chunks[i]->needRender = true;
//            }
//        }
    }

    void column(WorldGenRegion& region, int32_t x, int32_t y, int32_t z) {
        bool sky = true;

        for (; y >= 0; --y) {
            auto block_light = region.getData(x, y, z).getLightLevel();
            if (block_light > 0) {
                sources.emplace(x, y, z, 0);
                region.setLightFor(x, y, z, 0, block_light);
            }

            if (sky) {
                const auto state = region.getData(x, y, z);
                if (/*state.isOpaque() &&*/ state.isSolid()) {
                    sources.emplace(x, y + 1, z, 3);
                    sky = false;
                } else {
                    region.setLightFor(x, y, z, 3, 15);
                }
            } else {
                removes.emplace(x, y, z, 3, 0);

//            sources.emplace(x + 1, y, z, 3);
//            sources.emplace(x - 1, y, z, 3);

//            sources.emplace(x, y, z - 1, 3);
//            sources.emplace(x, y, z + 1, 3);

//            sources.emplace(x, y + 1, z, 3);
//            sources.emplace(x, y - 1, z, 3);

                region.setLightFor(x, y, z, 3, 0);
            }
        }
    }

    void calculate(WorldGenRegion& region, int32_t xPos, int32_t zPos) {
        std::bitset<9> mask{};

        for (int32_t x = xPos; x < xPos + 16; x++) {
            for (int32_t z = zPos; z < zPos + 16; z++) {
                column(region, x, 255, z);
            }
        }

        proccess(region, mask);
    }

    void update(WorldGenRegion& region, int32_t x, int32_t y, int32_t z, BlockData old, BlockData data) {
        std::bitset<9> mask{};

        if (/*data.isOpaque() &&*/ data.isSolid()) {
            removes.emplace(x, y, z, 3, region.getLightFor(x, y, z, 3));
            region.setLightFor(x, y, z, 3, 0);

            y -= 1;

            for (; y >= 0; --y) {
                removes.emplace(x, y, z, 3, region.getLightFor(x, y, z, 3));
                region.setLightFor(x, y, z, 3, 0);
            }
        } else {
//            removes.emplace(x, y, z, 0);

            for (int i = 0; i < 4; i++) {
                removes.emplace(x, y, z, i, 0);

//                sources.emplace(x + 1, y, z, i);
//                sources.emplace(x - 1, y, z, i);

//                sources.emplace(x, y, z - 1, i);
//                sources.emplace(x, y, z + 1, i);

//                sources.emplace(x, y + 1, z, i);
//                sources.emplace(x, y - 1, z, i);
            }
        }

        column(region, x, 255, z);

        const auto bl_light = data.getLightLevel();
        const auto light0 = region.getLightFor(x, y, z, 0);

        if (bl_light < light0) {
            removes.emplace(x, y, z, 0, light0);
        }
        region.setLightFor(x, y, z, 0, bl_light);

        if (bl_light > 0) {
            sources.emplace(x, y, z, 0);
        }

        proccess(region, mask);
    }
};

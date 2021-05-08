#pragma once

#include "../WorldGenRegion.hpp"
#include "../chunk/Chunk.hpp"
#include "../../block/Block.hpp"
#include "../../block/Blocks.hpp"

#include <tuple>
#include <queue>
#include <bitset>
#include <stack>
#include <chrono>
#include <mutex>

struct LightContext {
    WorldGenRegion region;
    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t>> sources;
    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t>> removes;
};

struct WorldLightManager {
    void remove(LightContext& ctx, int32_t x, int32_t y, int32_t z, int32_t channel, int32_t src_light, std::bitset<9>& mask) {
        const auto light = ctx.region.getLightFor(x, y, z, channel);

        if (light != 0 && light < src_light) {
            mask.set(ctx.region.toIndex(x >> 4, z >> 4), true);
            ctx.region.setLightFor(x, y, z, channel, 0);
            ctx.removes.emplace(x, y, z, channel, light);
        } else if (light >= src_light) {
            ctx.sources.emplace(x, y, z, channel);
        }
    }

    void propagate(LightContext& ctx, int32_t x, int32_t y, int32_t z, int32_t channel, int32_t src_light, std::bitset<9>& mask) {
        const auto light = ctx.region.getLightFor(x, y, z, channel);

        const auto new_light = src_light - 1;

        const auto state = ctx.region.getData(x, y, z);
        if (!(/*state.isOpaque() &&*/ state.isSolid()) && light < new_light) {
            mask.set(ctx.region.toIndex(x >> 4, z >> 4), true);

            ctx.region.setLightFor(x, y, z, channel, new_light);
            ctx.sources.emplace(x, y, z, channel);
        }
    }

    void proccess(LightContext& ctx, std::bitset<9>& mask) {
        while (!ctx.removes.empty()) {
            const auto [x, y, z, channel, light] = ctx.removes.front();
            ctx.removes.pop();

            if (x < ctx.region.bounds_max.x) {
                remove(ctx, x + 1, y, z, channel, light, mask);
            }
            if (x > ctx.region.bounds_min.x) {
                remove(ctx, x - 1, y, z, channel, light, mask);
            }
            if (z > ctx.region.bounds_min.y) {
                remove(ctx, x, y, z - 1, channel, light, mask);
            }
            if (z < ctx.region.bounds_max.y) {
                remove(ctx, x, y, z + 1, channel, light, mask);
            }
            if (y < 255) {
                remove(ctx, x, y + 1, z, channel, light, mask);
            }
//            if (y > 0) {
                remove(ctx, x, y - 1, z, channel, light, mask);
//            }
        }

        while (!ctx.sources.empty()) {
            const auto [x, y, z, channel] = ctx.sources.front();
            ctx.sources.pop();

            const auto light = ctx.region.getLightFor(x, y, z, channel);
            if (light <= 1) continue;

            if (x < ctx.region.bounds_max.x) {
                propagate(ctx, x + 1, y, z, channel, light, mask);
            }
            if (x > ctx.region.bounds_min.x) {
                propagate(ctx, x - 1, y, z, channel, light, mask);
            }
            if (z > ctx.region.bounds_min.y) {
                propagate(ctx, x, y, z - 1, channel, light, mask);
            }
            if (z < ctx.region.bounds_max.y) {
                propagate(ctx, x, y, z + 1, channel, light, mask);
            }
            if (y < 255) {
                propagate(ctx, x, y + 1, z, channel, light, mask);
            }
//            if (y > 0) {
                propagate(ctx, x, y - 1, z, channel, light, mask);
//            }
        }

//        for (int i = 0; i < 9; i++) {
//            if (mask.test(i)) {
//                region.chunks[i]->needRender = true;
//            }
//        }
    }

    void column(LightContext& ctx, int32_t x, int32_t y, int32_t z) {
        bool sky = true;

        for (; y >= 0; --y) {
            auto block_light = ctx.region.getData(x, y, z).getLightLevel();
            if (block_light > 0) {
                ctx.sources.emplace(x, y, z, 0);
                ctx.region.setLightFor(x, y, z, 0, block_light);
            }

            if (sky) {
                const auto state = ctx.region.getData(x, y, z);
                if (/*state.isOpaque() &&*/ state.isSolid()) {
                    sky = false;
                    ctx.sources.emplace(x, y + 1, z, 3);
//                    break;
                } else {
                    ctx.region.setLightFor(x, y, z, 3, 15);
                }
            } else {
                ctx.removes.emplace(x, y, z, 3, 0);

                ctx.region.setLightFor(x, y, z, 3, 0);
            }
        }
    }

    void calculate(LightContext& ctx, int32_t xPos, int32_t zPos) {
        using Clock = std::chrono::high_resolution_clock;

        std::bitset<9> mask{};

        for (int32_t x = xPos; x < xPos + 16; x++) {
            for (int32_t z = zPos; z < zPos + 16; z++) {
                column(ctx, x, 255, z);
            }
        }

        proccess(ctx, mask);
    }

    void update(LightContext& ctx, int32_t x, int32_t y, int32_t z, BlockData old, BlockData data) {
        std::bitset<9> mask{};

        if (/*data.isOpaque() &&*/ data.isSolid()) {
            {
                ctx.removes.emplace(x, y, z, 3, ctx.region.getLightFor(x, y, z, 3));
            }
            ctx.region.setLightFor(x, y, z, 3, 0);

            y -= 1;

            for (; y >= 0; --y) {
                ctx.removes.emplace(x, y, z, 3, ctx.region.getLightFor(x, y, z, 3));
                ctx.region.setLightFor(x, y, z, 3, 0);
            }
        } else {
            for (int i = 0; i < 4; i++) {
                ctx.removes.emplace(x, y, z, i, 0);
            }
        }

        column(ctx, x, 255, z);

        const auto bl_light = data.getLightLevel();
        const auto light0 = ctx.region.getLightFor(x, y, z, 0);

        if (bl_light < light0) {
            ctx.removes.emplace(x, y, z, 0, light0);
        }
        ctx.region.setLightFor(x, y, z, 0, bl_light);

        if (bl_light > 0) {
            ctx.sources.emplace(x, y, z, 0);
        }

        proccess(ctx, mask);
    }
};

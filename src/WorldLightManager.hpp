#pragma once

#include <tuple>
#include <queue>
#include <bitset>

#include "worldgenregion.hpp"

struct WorldLightManager {
    std::queue<glm::ivec3> sources;
    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t>> removes;

    void remove(WorldGenRegion& region, int32_t x, int32_t y, int32_t z, int32_t src_light, std::bitset<9>& mask) {
        const auto light = region.getSkyLight(x, y, z);

        if (light != 0 && light < src_light) {
            mask.set(region.toIndex(x >> 4, z >> 4), true);

            region.setSkyLight(x, y, z, 0);
            removes.emplace(x, y, z, light);
        } else if (light >= src_light) {
            sources.emplace(x, y, z);
        }
    }

    void propagate(WorldGenRegion& region, int32_t x, int32_t y, int32_t z, int32_t src_light, std::bitset<9>& mask) {
        const auto light = region.getSkyLight(x, y, z);

        const auto new_light = src_light - 1;

        if (region.getData(x, y, z).id == BlockID::AIR && light < new_light) {
            mask.set(region.toIndex(x >> 4, z >> 4), true);

            region.setSkyLight(x, y, z, new_light);
            sources.emplace(x, y, z);
        }
    }

    void proccess(WorldGenRegion& region, std::bitset<9>& mask) {
        while (!removes.empty()) {
            const auto [x, y, z, light] = removes.front();
            removes.pop();

            remove(region, x + 1, y, z, light, mask);
            remove(region, x - 1, y, z, light, mask);

            remove(region, x, y, z - 1, light, mask);
            remove(region, x, y, z + 1, light, mask);

            remove(region, x, y + 1, z, light, mask);
            remove(region, x, y - 1, z, light, mask);
        }

        while (!sources.empty()) {
            const auto [x, y, z] = sources.front();
            sources.pop();

            const auto light = region.getSkyLight(x, y, z);
            if (light <= 1) continue;

            propagate(region, x + 1, y, z, light, mask);
            propagate(region, x - 1, y, z, light, mask);

            propagate(region, x, y, z - 1, light, mask);
            propagate(region, x, y, z + 1, light, mask);

            propagate(region, x, y + 1, z, light, mask);
            propagate(region, x, y - 1, z, light, mask);
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
            if (region.getData(x, y, z).id != BlockID::AIR) {
                sources.emplace(x, y + 1, z);
                break;
            }

            region.setSkyLight(x, y, z, 15);
        }

        for (; y >= 0; --y) {
//            removes.emplace(x, y, z, 0);

            sources.emplace(x + 1, y, z);
            sources.emplace(x - 1, y, z);

            sources.emplace(x, y, z - 1);
            sources.emplace(x, y, z + 1);

            sources.emplace(x, y + 1, z);
            sources.emplace(x, y - 1, z);

            region.setSkyLight(x, y, z, 0);
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

        if (data.id != BlockID::AIR) {
            removes.emplace(x, y, z, region.getSkyLight(x, y, z));
            region.setSkyLight(x, y, z, 0);

            y -= 1;

            for (; y >= 0; --y) {
                removes.emplace(x, y, z, region.getSkyLight(x, y, z));
                region.setSkyLight(x, y, z, 0);
            }
        } else {
//            removes.emplace(x, y, z, 0);

            sources.emplace(x + 1, y, z);
            sources.emplace(x - 1, y, z);

            sources.emplace(x, y, z - 1);
            sources.emplace(x, y, z + 1);

            sources.emplace(x, y + 1, z);
            sources.emplace(x, y - 1, z);
        }

        column(region, x, z);

        proccess(region, mask);
    }
};

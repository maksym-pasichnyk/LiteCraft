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

template <typename T>
concept LightReader = requires(T& self) {
    requires requires(int x, int y, int z, int channel, int val) {
        { self.setLightFor(x, y, z, channel, val)};
    };
    requires requires(int x, int y, int z, int channel) {
        { self.getLightFor(x, y, z, channel)} -> std::same_as<int>;
    };
    requires requires(HeightmapType type, int x, int z) {
        { self.getHeight(type, x, z)} -> std::same_as<int>;
    };
    requires requires(int x, int y, int z) {
        { self.getData(x, y, z)} -> std::same_as<BlockData>;
    };
    requires requires(int x, int z) {
        { self.getChunk(x, z) } -> std::same_as<Chunk*>;
    };
};

struct WorldLightManager {
    std::mutex light_mutex{};

    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t>> sources;
    std::queue<std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t>> removes;
    
    enum LightType {
        SKY,
        BLOCK
    };

    void remove(LightReader auto& reader, int32_t x, int32_t y, int32_t z, int32_t channel, int32_t src_light) {
        const auto light = reader.getLightFor(x, y, z, channel);

        if (light != 0 && light < src_light) {
            reader.setLightFor(x, y, z, channel, 0);
            removes.emplace(x, y, z, channel, light);
        } else if (light >= src_light) {
            sources.emplace(x, y, z, channel);
        }
    }

    void propagate(LightReader auto& reader, int32_t x, int32_t y, int32_t z, int32_t channel, int32_t src_light) {
        const auto light = reader.getLightFor(x, y, z, channel);

        const auto state = reader.getData(x, y, z);
        if (!(/*state.isOpaque() &&*/ state.isSolid()) && light + 2 <= src_light) {
            reader.setLightFor(x, y, z, channel, src_light - 1);
            sources.emplace(x, y, z, channel);
        }
    }

    void proccess(LightReader auto& reader) {
        while (!removes.empty()) {
            const auto [x, y, z, channel, light] = removes.front();
            removes.pop();

            for (int i : {-1, 1}) {
                remove(reader, x + i, y, z, channel, light);
                remove(reader, x, y + i, z, channel, light);
                remove(reader, x, y, z + i, channel, light);
            }
        }

        while (!sources.empty()) {
            const auto [x, y, z, channel] = sources.front();
            sources.pop();

            const auto light = reader.getLightFor(x, y, z, channel);
            if (light <= 1) continue;

            for (int i : {-1, 1}) {
                propagate(reader, x + i, y, z, channel, light);
                propagate(reader, x, y + i, z, channel, light);
                propagate(reader, x, y, z + i, channel, light);
            }
        }
    }

    void column(LightReader auto& reader, int32_t x, int32_t y, int32_t z) {
        const int max_y = std::max(
            std::max(
                reader.getHeight(HeightmapType::WORLD_SURFACE, x - 1, z),
                reader.getHeight(HeightmapType::WORLD_SURFACE, x + 1, z)
            ),
            std::max(
                reader.getHeight(HeightmapType::WORLD_SURFACE, x, z - 1),
                reader.getHeight(HeightmapType::WORLD_SURFACE, x, z + 1)
            )
        );

        for (; y >= 0; --y) {
            const auto state = reader.getData(x, y, z);
            if (state.isSolid()) {
                break;
            }

            reader.setLightFor(x, y, z, SKY, 15);
        }

        for (; y <= max_y; ++y) {
            sources.emplace(x, y, z, SKY);
        }
    }

    void calculate(LightReader auto& reader, int32_t xstart, int32_t zstart) {
        light_mutex.lock();
        for (int32_t x = xstart; x < xstart + 16; x++) {
            for (int32_t z = zstart; z < zstart + 16; z++) {
                column(reader, x, 255, z);
            }
        }

        auto chunk = reader.getChunk(xstart >> 4, zstart >> 4);
        for (auto pos : chunk->getLightSources()) {
            const auto level = chunk->getLightLevel(pos);
            if (level > 0) {
                sources.emplace(pos.x, pos.y, pos.z, BLOCK);
                reader.setLightFor(pos.x, pos.y, pos.z, BLOCK, level);
            }
        }

        proccess(reader);
        light_mutex.unlock();
    }

    void update(LightReader auto& reader, int32_t x, int32_t y, int32_t z, BlockData old, BlockData data) {
        light_mutex.lock();

        const auto bl_light_source = data.getLightLevel();
        const auto bl_light = reader.getLightFor(x, y, z, BLOCK);

        removes.emplace(x, y, z, BLOCK, bl_light);
        reader.setLightFor(x, y, z, BLOCK, bl_light_source);

        if (bl_light_source > 0) {
            sources.emplace(x, y, z, BLOCK);
        }

        if (/*data.isOpaque() &&*/ data.isSolid()) {
            for (; y >= 0; --y) {
                const auto sl_light = reader.getLightFor(x, y, z, SKY);
                if (sl_light == 0) {
                    break;
                }
                removes.emplace(x, y, z, SKY, sl_light);
                reader.setLightFor(x, y, z, SKY, 0);
            }
        } else {
            for (int i : {-1, 1}) {
                if (reader.getLightFor(x + i, y, z, SKY) > 0) {
                    sources.emplace(x + i, y, z, SKY);
                }
                if (reader.getLightFor(x, y + i, z, SKY) > 0) {
                    sources.emplace(x, y + i, z, SKY);
                }
                if (reader.getLightFor(x, y, z + i, SKY) > 0) {
                    sources.emplace(x, y, z + i, SKY);
                }
            }
//            removes.emplace(x, y, z, SKY, 0);
        }

        // todo: optimize
        column(reader, x, 255, z);

        proccess(reader);
        light_mutex.unlock();
    }
};

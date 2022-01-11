#pragma once

#include "../../block/BlockReader.hpp"
#include "../../block/BlockTable.hpp"
#include "../../util/math/BoundingBox.hpp"
#include "../../util/math/ChunkPos.hpp"
#include "../gen/Heightmap.hpp"
#include "Json.hpp"

#include <set>
#include <map>
#include <span>
#include <queue>
#include <vector>
#include <memory>
#include <atomic>
#include <bitset>
#include <cstdint>
#include <cassert>
#include <functional>
#include <glm/vec3.hpp>
#include <spdlog/spdlog.h>

struct WorldGenRegion;

struct ChunkSection {
    std::array<BlockData, 4096> blocks{};
};

struct LightSection {
    std::array<uint8_t, 2048> lights;

    void setLight(int x, int y, int z, int new_light) {
        const auto val = new_light & 0xF;
        const auto idx = toIndex(x, y, z);
        auto& light = lights[idx >> 1];
        light = ((idx & 1) == 1)
                ? ((light & 0x0F) | (val << 4))
                : ((light & 0xF0) | val);
    }

    auto getLight(int x, int y, int z) const -> int {
        const auto idx = toIndex(x, y, z);
        const auto light = lights[idx >> 1];
        return (((idx & 1) == 1) ? (light >> 4) : light) & 0xF;
    }

private:
    static constexpr auto toIndex(int x, int y, int z) noexcept -> size_t {
        return (y << 8) | (z << 4) | x;
    }
};

struct Structure;
struct StructureStart;
struct Chunk {
    ChunkPos coords;
	std::array<std::unique_ptr<ChunkSection>, 16> sections{};
    std::array<std::unique_ptr<LightSection>, 18> skyLightSections{};
    std::array<std::unique_ptr<LightSection>, 18> blockLightSections{};
    std::array<Heightmap, 6> heightmaps{};

    std::map<Structure*, StructureStart*> starts;
    std::map<Structure*, std::set<int64_t>> references;

    std::bitset<65536> carvingMask;
    std::vector<BlockPos> blockLightSources;

    explicit Chunk(const ChunkPos& pos) : coords{pos} {}

    auto getLightSources() -> std::span<const BlockPos> {
        return blockLightSources;
    }

    void setBlockLight(int x, int y, int z, int val) {
        auto& section = blockLightSections[(y >> 4) + 1];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<LightSection>();
        }
        section->setLight(x & 15, y & 15, z & 15, val);
    }

    auto getBlockLight(int x, int y, int z) const -> int {
        auto section = blockLightSections[(y >> 4) + 1].get();
        if (section == nullptr) {
            return 0;
        }
        return section->getLight(x & 15, y & 15, z & 15);
    }

    void setSkyLight(int x, int y, int z, int val) {
        auto& section = skyLightSections[(y >> 4) + 1];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<LightSection>();
        }
        section->setLight(x & 15, y & 15, z & 15, val);
    }

    auto getSkyLight(int x, int y, int z) const -> int {
        auto section = skyLightSections[(y >> 4) + 1].get();
        if (section == nullptr) {
            return 0;
        }
        return section->getLight(x & 15, y & 15, z & 15);
    }

    auto getLightLevel(const BlockPos& pos) const -> int {
        return getData(pos).getLightLevel();
    }

    bool setData(const BlockPos& pos, BlockData data) {
        return setData(pos.x, pos.y, pos.z, data);
    }

    bool setData(int x, int y, int z, BlockData data) {
    	auto& section = sections[y >> 4];
    	if (section == nullptr) {
    	    if (data.isAir()) {
    	        return false;
    	    }
    		section = std::make_unique<ChunkSection>();
    	}
        section->blocks[toIndex(x & 15, y & 15, z & 15)] = data;
        updateHeightmap(x & 15, y, z & 15, data);

        if (data.getLightLevel() > 0) {
            blockLightSources.emplace_back(coords.getBlockX(x & 15), y, coords.getBlockZ(z & 15));
        }
    	return true;
    }

    void updateHeightmap(int x, int y, int z, BlockData data) {
        const auto types = std::array{
            HeightmapType::WORLD_SURFACE_WG,
            HeightmapType::WORLD_SURFACE,
            HeightmapType::OCEAN_FLOOR_WG,
            HeightmapType::OCEAN_FLOOR,
            HeightmapType::MOTION_BLOCKING,
            HeightmapType::MOTION_BLOCKING_NO_LEAVES
        };

        const auto i = x | (z << 4);
        for (auto type : types) {
            auto& heightmap = heightmaps.at(static_cast<size_t>(type));

            const auto predicate = HeightmapUtils::predicate(type);
            const auto height = heightmap.getAt(i);

            if (y > height - 2) {
                if (predicate(data)) {
                    if (y >= height) {
                        heightmap.setAt(i, y + 1);
                    }
                } else if (height - 1 == y) {
                    heightmap.setAt(i, 0);

                    for (int y1 = y - 1; y1 >= 0; --y1) {
                        if (predicate(getData(x, y1, z))) {
                            heightmap.setAt(i, y1 + 1);
                            break;
                        }
                    }
                }
            }
        }
    }

    auto getData(const BlockPos& pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

    auto getData(int x, int y, int z) const -> BlockData {
    	auto section = sections[y >> 4].get();
    	if (section == nullptr) {
			return {};
    	}
        return section->blocks[toIndex(x & 15, y & 15, z & 15)];
    }

    auto getBlock(int x, int y, int z) const -> Block* {
        return getData(x, y, z).getBlock();
    }

    auto getHeight(HeightmapType type, const BlockPos& pos) -> BlockPos {
        const auto y = getHeight(type, pos.x, pos.z);
        return BlockPos::from(pos.x, y, pos.z);
    }

    auto getHeight(HeightmapType type, int x, int z) -> int {
        return heightmaps.at(static_cast<size_t>(type)).get(x & 15, z & 15);
    }

    auto getTopBlockY(HeightmapType type, int x, int z) -> int {
        return getHeight(type, x, z) - 1;
    }

    static constexpr auto toIndex(int x, int y, int z) noexcept -> int {
        return (x << 8) | (z << 4) | y;
    }

    void addStructureStart(Structure* structure, StructureStart* start) {
        starts.emplace(structure, start);
    }

    void updateHeightmaps() {
        for (int z = 0; z < 16; z++) {
            for (int x = 0; x < 16; x++) {
                const int i = x | (z << 4);

                for (int y = 255; y >= 0; y--) {
                    if (!getData(x, y, z).isAir()) {
                        heightmaps[0].setAt(i, y + 1);
                        break;
                    }
                }
            }
        }
    }
};

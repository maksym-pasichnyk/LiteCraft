#pragma once

#include "../gen/Heightmap.hpp"
#include "../../mesh.hpp"
#include "../../block/BlockTable.hpp"
#include "../../block/BlockReader.hpp"
#include "../../util/math/ChunkPos.hpp"
#include "../../util/math/BoundingBox.hpp"

#include <map>
#include <queue>
#include <vector>
#include <memory>
#include <atomic>
#include <bitset>
#include <cstdint>
#include <cassert>
#include <functional>
#include <glm/vec3.hpp>
#include <fmt/format.h>

struct WorldGenRegion;

struct SimpleVBuffer {
    std::vector<Vertex> vertices;
    std::vector<int32_t> indices;

    void clear() {
        vertices.clear();
        indices.clear();
    }

	void quad(int a1, int b1, int c1, int a2, int b2, int c2) {
        auto i = vertices.size();
        indices.reserve(6);
        indices.push_back(i + a1);
        indices.push_back(i + b1);
        indices.push_back(i + c1);
        indices.push_back(i + a2);
        indices.push_back(i + b2);
        indices.push_back(i + c2);
    }

	void quad(int a1, int b1, int c1, int d1, int a2, int b2, int c2, int d2) {
        auto i = vertices.size();
        indices.reserve(8);
        indices.push_back(i + a1);
        indices.push_back(i + b1);
        indices.push_back(i + c1);
        indices.push_back(i + d1);
        indices.push_back(i + a2);
        indices.push_back(i + b2);
        indices.push_back(i + c2);
        indices.push_back(i + d2);
    }

	void quad() {
        quad(0, 1, 2, 0, 2, 3);
    }
    void quadInv() {
        quad(0, 2, 1, 0, 3, 2);
    }

    void vertex(float x, float y, float z, float u, float v, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        vertices.push_back(Vertex{
			.point{x, y, z},
			.tex{u, v},
			.color{r, g, b, a}
        });
    }
};

struct ChunkSection {
    std::array<BlockData, 4096> blocks{};
};

struct LightSection {
    std::array<uint8_t, 2048> lights;

    void setLight(int32_t x, int32_t y, int32_t z, int32_t new_light) {
        const auto val = new_light & 0xF;
        const auto idx = toIndex(x, y, z);
        auto& light = lights[idx >> 1];
        light = ((idx & 1) == 1)
                ? ((light & 0x0F) | (val << 4))
                : ((light & 0xF0) | val);
    }

    auto getLight(int32_t x, int32_t y, int32_t z) const -> int32_t {
        const auto idx = toIndex(x, y, z);
        const auto light = lights[idx >> 1];
        return (((idx & 1) == 1) ? (light >> 4) : light) & 0xF;
    }

private:
    static constexpr auto toIndex(int32_t x, int32_t y, int32_t z) noexcept -> size_t {
        return (y << 8) | (z << 4) | x;
    }
};

struct Structure;
struct StructureStart;
struct Chunk {
    ChunkPos pos;
	std::array<std::unique_ptr<ChunkSection>, 16> sections{};
    std::array<std::unique_ptr<LightSection>, 18> skyLightSections{};
    std::array<std::unique_ptr<LightSection>, 18> blockLightSections{};
    std::array<Heightmap, 5> heightmaps{};

    std::map<Structure*, StructureStart*> structureStarts;
    std::bitset<65536> carvingMask;

    std::vector<BlockPos> blockLightSources;

//    std::vector<std::shared_ptr<StructureStart>> structureReferences;

    explicit Chunk(ChunkPos pos) : pos{pos} {}

    std::span<BlockPos> getLightSources() {
        return blockLightSources;
    }

    void setBlockLight(int32_t x, int32_t y, int32_t z, int32_t val) {
        auto& section = blockLightSections[(y >> 4) + 1];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<LightSection>();
        }
        section->setLight(x & 15, y & 15, z & 15, val);
    }

    auto getBlockLight(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto section = blockLightSections[(y >> 4) + 1].get();
        if (section == nullptr) {
            return 0;
        }
        return section->getLight(x & 15, y & 15, z & 15);
    }

    void setSkyLight(int32_t x, int32_t y, int32_t z, int32_t val) {
        auto& section = skyLightSections[(y >> 4) + 1];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<LightSection>();
        }
        section->setLight(x & 15, y & 15, z & 15, val);
    }

    auto getSkyLight(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto section = skyLightSections[(y >> 4) + 1].get();
        if (section == nullptr) {
            return 0;
        }
        return section->getLight(x & 15, y & 15, z & 15);
    }

    auto getLightLevel(const BlockPos& pos) const -> int32_t {
        return getData(pos).getLightLevel();
    }

    bool setData(const BlockPos& pos, BlockData data) {
        return setData(pos.x, pos.y, pos.z, data);
    }

    bool setData(int32_t x, int32_t y, int32_t z, BlockData data) {
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
            blockLightSources.emplace_back((x & 15) + pos.getStartX(), y, (z & 15) + pos.getStartZ());
        }
    	return true;
    }

    void updateHeightmap(int32_t x, int32_t y, int32_t z, BlockData data) {
        const int32_t i = x | (z << 4);
        const int32_t height = heightmaps[0].getAt(i);

        if (y > height - 2) {
            if (!data.isAir()) {
                if (y >= height) {
                    heightmaps[0].setAt(i, y + 1);
                }
            } else if (height - 1 == y) {
                for (int y1 = y - 1; y1 >= 0; --y1) {
                    if (!getData(x, y1, z).isAir()) {
                        heightmaps[0].setAt(i, y1 + 1);
                        break;
                    }
                }
                heightmaps[0].setAt(i, 0);
            }
        }
    }

    auto getData(const BlockPos& pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
    	auto section = sections[y >> 4].get();
    	if (section == nullptr) {
			return {};
    	}
        return section->blocks[toIndex(x & 15, y & 15, z & 15)];
    }

    auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
        return getData(x, y, z).getBlock();
    }

    auto getHeight(HeightmapType type, int32_t x, int32_t z) -> int32_t {
        return heightmaps[0].get(x, z);
    }

    auto getTopBlockY(HeightmapType type, int32_t x, int32_t z) -> int32_t {
        return getHeight(type, x, z) - 1;
    }

    static constexpr auto toIndex(int32_t x, int32_t y, int32_t z) noexcept -> int32_t {
        return (x << 8) | (z << 4) | y;
    }

    void addStructureStart(Structure* structure, StructureStart* start) {
        structureStarts.emplace(structure, start);
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

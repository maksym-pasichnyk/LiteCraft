#pragma once

#include "../gen/Heightmap.hpp"
#include "../../block/BlockTable.hpp"
#include "../../block/BlockReader.hpp"
#include "../../mesh.hpp"
#include "../../util/math/ChunkPos.hpp"
#include "../../util/math/BoundingBox.hpp"

#include <glm/vec3.hpp>

#include <map>
#include <vector>
#include <memory>
#include <cassert>
#include <queue>
#include <cstdint>
#include <functional>
#include <fmt/format.h>
#include <atomic>

struct WorldGenRegion;

struct RenderLayerBuilder {
	std::vector<Vertex>& vertices;
	std::vector<int>& indices;

	void quad() {
        auto i = vertices.size();
        indices.push_back(i + 0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i + 0);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
    }
    void quadInv() {
        auto i = vertices.size();
        indices.push_back(i + 0);
        indices.push_back(i + 2);
        indices.push_back(i + 1);
        indices.push_back(i + 0);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }

    void vertex(float x, float y, float z, float u, float v, uint8_t r, uint8_t g, uint8_t b, int32_t packedLight, float ao) {
        vertices.push_back(Vertex{
            .point{x, y, z},
            .tex{u, v},
            .color{r, g, b, ao * 255},
            .light{
                ((packedLight >> 0) & 0xF) * 17,
                0,
                0,
                ((packedLight >> 4) & 0xF) * 17
            }
        });
    }
};

enum class RenderLayer;

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

#include <fmt/format.h>

struct RenderBuffer {
    std::vector<Vertex> vertices;
    std::array<std::vector<int32_t>, 3> indices{};

    RenderBuffer() {
        vertices.reserve(20000);
        indices[0].reserve(20000);
        indices[1].reserve(20000);
        indices[2].reserve(20000);
    }

	auto getForLayer(RenderLayer layer) -> RenderLayerBuilder {
		return RenderLayerBuilder {
			.vertices = vertices,
			.indices = indices[static_cast<size_t>(layer)]
		};
	}

    void clear() {
        vertices.clear();
        for (auto& submesh : indices) {
        	submesh.clear();
        }
    }
};

/*enum class ChunkState {
	Empty,
	StructureStart,
	StructureReferences,
	Biomes,
	Noise,
	Surface,
	Features,
	Light,
	Full
};*/

struct ChunkSection {
    std::array<BlockData, 4096> blocks{};
};

//struct StructurePiece {
//    DIRECTION coordBaseMode;
//    BoundingBox boundingBox;
//
//    virtual ~StructurePiece() = default;
//
//    virtual void place(WorldGenRegion& region, BoundingBox bb) = 0;
//
//    int get_x_with_offset(int x, int z) {
//        switch (coordBaseMode) {
//            case SOUTH:
//            case NORTH:
//                return boundingBox.minX + x;
//            case WEST:
//                return boundingBox.maxX - z;
//            case EAST:
//                return boundingBox.minX + z;
//        }
//        return x;
//    }
//
//    int get_y_with_offset(int y) {
//        return boundingBox.minY + y;
//    }
//
//    int get_z_with_offset(int x, int z) {
//        switch (coordBaseMode) {
//            case NORTH:
//                return boundingBox.maxZ - z;
//            case SOUTH:
//                return boundingBox.minZ + z;
//            case WEST:
//            case EAST:
//                return boundingBox.minZ + x;
//        }
//        return z;
//    }
//
//    auto setBlock(IBlockReader auto &blocks, BoundingBox sbb, int x, int y, int z, BlockData blockData) {
//        BlockPos blockpos{get_x_with_offset(x, z), get_y_with_offset(y), get_z_with_offset(x, z)};
//
//        if (sbb.contains(blockpos.x, blockpos.y, blockpos.z)) {
//            if (coordBaseMode == EAST || coordBaseMode == NORTH) {
//                auto val = 0;
//                if (blockData.dv & BlockPane_WEST) {
//                    val |= BlockPane_WEST;
//                }
//                if (blockData.dv & BlockPane_NORTH) {
//                    val |= BlockPane_SOUTH;
//                }
//                if (blockData.dv & BlockPane_EAST) {
//                    val |= BlockPane_EAST;
//                }
//                if (blockData.dv & BlockPane_SOUTH) {
//                    val |= BlockPane_NORTH;
//                }
//                blockData.dv = val;
//            }
//
//            if (coordBaseMode == EAST || coordBaseMode == WEST) {
//                auto val = 0;
//                if (blockData.dv & BlockPane_WEST) {
//                    val |= BlockPane_SOUTH;
//                }
//                if (blockData.dv & BlockPane_NORTH) {
//                    val |= BlockPane_WEST;
//                }
//                if (blockData.dv & BlockPane_EAST) {
//                    val |= BlockPane_NORTH;
//                }
//                if (blockData.dv & BlockPane_SOUTH) {
//                    val |= BlockPane_EAST;
//                }
//                blockData.dv = val;
//            }
//
//            blocks.setData(blockpos.x, blockpos.y, blockpos.z, blockData);
//        }
//    }
//};

//struct StructureStart {
//    BoundingBox boundingBox;
//    std::vector<std::unique_ptr<StructurePiece>> pieces;
//
//    virtual ~StructureStart() = default;
//    virtual void build(int pos_x, int pos_z) = 0;
//
//    void updateBoundingBox() {
//        boundingBox.minX = std::numeric_limits<int>::max();
//        boundingBox.minY = std::numeric_limits<int>::max();
//        boundingBox.minZ = std::numeric_limits<int>::max();
//        boundingBox.maxX = std::numeric_limits<int>::min();
//        boundingBox.maxY = std::numeric_limits<int>::min();
//        boundingBox.maxZ = std::numeric_limits<int>::min();
//
//        for (auto& piece : pieces) {
//            boundingBox.minX = std::min(boundingBox.minX, piece->boundingBox.minX);
//            boundingBox.minY = std::min(boundingBox.minY, piece->boundingBox.minY);
//            boundingBox.minZ = std::min(boundingBox.minZ, piece->boundingBox.minZ);
//            boundingBox.maxX = std::max(boundingBox.maxX, piece->boundingBox.maxX);
//            boundingBox.maxY = std::max(boundingBox.maxY, piece->boundingBox.maxY);
//            boundingBox.maxZ = std::max(boundingBox.maxZ, piece->boundingBox.maxZ);
//        }
//    }
//};

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

struct Lightmap {
    std::array<uint8_t, 4096> lights;

    auto getBlockLight(int32_t x, int32_t y, int32_t z) -> int32_t {
        return static_cast<int32_t>((lights[toIndex(x, y, z)] >> 0) & 0xF);
    }

    auto getSkyLight(int32_t x, int32_t y, int32_t z) -> int32_t {
        return static_cast<int32_t>((lights[toIndex(x, y, z)] >> 4) & 0xF);
    }

    void setBlockLight(int32_t x, int32_t y, int32_t z, int32_t val) {
        lights[toIndex(x, y, z)] = (lights[toIndex(x, y, z)] & 0xFFF0) | ((val & 0xF) << 0);
    }

    void setSkyLight(int32_t x, int32_t y, int32_t z, int32_t val) {
        lights[toIndex(x, y, z)] = (lights[toIndex(x, y, z)] & 0xFF0F) | ((val & 0xF) << 4);
    }

    void setLight(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val) {
        (this->*(channel == 0 ? &Lightmap::setBlockLight : &Lightmap::setSkyLight))(x, y, z, val);
    }

    auto getLight(int32_t x, int32_t y, int32_t z, int32_t channel) -> int32_t {
        return (this->*(channel == 0 ? &Lightmap::getBlockLight : &Lightmap::getSkyLight))(x, y, z);
    }

    auto getLightPacked(int32_t x, int32_t y, int32_t z) -> int32_t {
        return lights[toIndex(x, y, z)];
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
//    std::array<std::unique_ptr<LightSection>, 16> skyLightSections{};
//    std::array<std::unique_ptr<LightSection>, 16> blockLightSections{};

    std::array<std::unique_ptr<Lightmap>, 18> lightSections{};

    std::array<Heightmap, 5> heightmaps{};

    std::map<Structure*, StructureStart*> structureStarts;
//    std::vector<std::shared_ptr<StructureStart>> structureReferences;

    explicit Chunk(ChunkPos pos) : pos{pos} {}

//    void setSkyLight(int32_t x, int32_t y, int32_t z, int32_t new_light) {
//        auto& section = skyLightSections[y >> 4];
//        if (section == nullptr) {
//            if (new_light == /*15*/0) {
//                return;
//            }
//            section = std::make_unique<LightSection>();
//        }
//        section->setLightFor(x & 15, y & 15, z & 15, /*15 -*/ new_light);
//    }
//
//    auto getSkyLight(int32_t x, int32_t y, int32_t z) const -> int32_t {
//        auto& section = skyLightSections[y >> 4];
//        if (section == nullptr) {
//            return /*15*/0;
//        }
//        return /*15 - */section->getLightFor(x & 15, y & 15, z & 15);
//    }
//
//    void setBlockLight(int32_t x, int32_t y, int32_t z, int32_t new_light) {
//        auto& section = blockLightSections[y >> 4];
//        if (section == nullptr) {
//            if (new_light == 0) {
//                return;
//            }
//            section = std::make_unique<LightSection>();
//        }
//        section->setLightFor(x & 15, y & 15, z & 15, new_light);
//    }
//
//    auto getBlockLight(int32_t x, int32_t y, int32_t z) const -> int32_t {
//        auto& section = blockLightSections[y >> 4];
//        if (section == nullptr) {
//            return 0;
//        }
//        return section->getLightFor(x & 15, y & 15, z & 15);
//    }

    void setLight(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val) {
        auto& section = lightSections[(y >> 4) + 1];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<Lightmap>();
        }
        section->setLight(x & 15, y & 15, z & 15, channel, val);
    }

    auto getLight(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t {
        auto section = lightSections[(y >> 4) + 1].get();
        if (section == nullptr) {
            return 0;
        }
        return section->getLight(x & 15, y & 15, z & 15, channel);
    }

    auto getLightPacked(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto& section = lightSections[(y >> 4) + 1];
        if (section == nullptr) {
            return 0;
        }
        return section->getLightPacked(x & 15, y & 15, z & 15);
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
        updateHeightmap(x & 15, y, z & 15, data);
    	section->blocks[toIndex(x & 15, y & 15, z & 15)] = data;
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

#pragma once

#include "../gen/Heightmap.hpp"
#include "../../block/BlockTable.hpp"
#include "../../block/BlockReader.hpp"
#include "../../mesh.hpp"
#include "../../util/math/ChunkPos.hpp"
#include "../../util/math/BoundingBox.hpp"

#include <glm/vec3.hpp>

#include <vector>
#include <memory>
#include <cassert>
#include <queue>
#include <cstdint>

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
                ((packedLight >> 4) & 0xF) * 17,
                ((packedLight >> 8) & 0xF) * 17,
                ((packedLight >> 12) & 0xF) * 17
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

struct RenderBuffer {
    std::vector<Vertex> vertices;
    std::vector<int32_t> indices[3]{};

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

struct ChunkLayer {
    int32_t index_offset = 0;
    int32_t index_count = 0;
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

enum DIRECTION {
    SOUTH = 0,
    EAST = 3,
    NORTH = 2,
    WEST = 1
};

enum {
    BlockPane_WEST = 1,
    BlockPane_NORTH = 2,
    BlockPane_EAST = 4,
    BlockPane_SOUTH = 8,
};

#include <fmt/format.h>

struct StructurePiece {
    DIRECTION coordBaseMode;
    BoundingBox boundingBox;

    virtual ~StructurePiece() = default;

    virtual void place(WorldGenRegion& region, BoundingBox bb) = 0;

    int get_x_with_offset(int x, int z) {
        switch (coordBaseMode) {
            case SOUTH:
            case NORTH:
                return boundingBox.minX + x;
            case WEST:
                return boundingBox.maxX - z;
            case EAST:
                return boundingBox.minX + z;
        }
        return x;
    }

    int get_y_with_offset(int y) {
        return boundingBox.minY + y;
    }

    int get_z_with_offset(int x, int z) {
        switch (coordBaseMode) {
            case NORTH:
                return boundingBox.maxZ - z;
            case SOUTH:
                return boundingBox.minZ + z;
            case WEST:
            case EAST:
                return boundingBox.minZ + x;
        }
        return z;
    }

    auto setBlock(IBlockReader auto &blocks, BoundingBox sbb, int x, int y, int z, BlockData blockData) {
        BlockPos blockpos{get_x_with_offset(x, z), get_y_with_offset(y), get_z_with_offset(x, z)};

        if (sbb.contains(blockpos.x, blockpos.y, blockpos.z)) {
            if (coordBaseMode == EAST || coordBaseMode == NORTH) {
                auto val = 0;
                if (blockData.dv & BlockPane_WEST) {
                    val |= BlockPane_WEST;
                }
                if (blockData.dv & BlockPane_NORTH) {
                    val |= BlockPane_SOUTH;
                }
                if (blockData.dv & BlockPane_EAST) {
                    val |= BlockPane_EAST;
                }
                if (blockData.dv & BlockPane_SOUTH) {
                    val |= BlockPane_NORTH;
                }
                blockData.dv = val;
            }

            if (coordBaseMode == EAST || coordBaseMode == WEST) {
                auto val = 0;
                if (blockData.dv & BlockPane_WEST) {
                    val |= BlockPane_SOUTH;
                }
                if (blockData.dv & BlockPane_NORTH) {
                    val |= BlockPane_WEST;
                }
                if (blockData.dv & BlockPane_EAST) {
                    val |= BlockPane_NORTH;
                }
                if (blockData.dv & BlockPane_SOUTH) {
                    val |= BlockPane_EAST;
                }
                blockData.dv = val;
            }

            blocks.setData(blockpos.x, blockpos.y, blockpos.z, blockData);
        }
    }
};

struct StructureStart {
    BoundingBox boundingBox;
    std::vector<std::unique_ptr<StructurePiece>> pieces;

    virtual ~StructureStart() = default;
    virtual void build(int pos_x, int pos_z) = 0;

    void updateBoundingBox() {
        boundingBox.minX = std::numeric_limits<int>::max();
        boundingBox.minY = std::numeric_limits<int>::max();
        boundingBox.minZ = std::numeric_limits<int>::max();
        boundingBox.maxX = std::numeric_limits<int>::min();
        boundingBox.maxY = std::numeric_limits<int>::min();
        boundingBox.maxZ = std::numeric_limits<int>::min();

        for (auto& piece : pieces) {
            boundingBox.minX = std::min(boundingBox.minX, piece->boundingBox.minX);
            boundingBox.minY = std::min(boundingBox.minY, piece->boundingBox.minY);
            boundingBox.minZ = std::min(boundingBox.minZ, piece->boundingBox.minZ);
            boundingBox.maxX = std::max(boundingBox.maxX, piece->boundingBox.maxX);
            boundingBox.maxY = std::max(boundingBox.maxY, piece->boundingBox.maxY);
            boundingBox.maxZ = std::max(boundingBox.maxZ, piece->boundingBox.maxZ);
        }
    }
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

struct Lightmap {
    std::array<uint16_t, 4096> lights;

    auto getLightR(int32_t x, int32_t y, int32_t z) -> int32_t {
        return static_cast<int32_t>((lights[toIndex(x, y, z)] >> 0) & 0xF);
    }

    auto getLightG(int32_t x, int32_t y, int32_t z) -> int32_t {
        return static_cast<int32_t>((lights[toIndex(x, y, z)] >> 4) & 0xF);
    }

    auto getLightB(int32_t x, int32_t y, int32_t z) -> int32_t {
        return static_cast<int32_t>((lights[toIndex(x, y, z)] >> 8) & 0xF);
    }

    auto getLightS(int32_t x, int32_t y, int32_t z) -> int32_t {
        return static_cast<int32_t>((lights[toIndex(x, y, z)] >> 12) & 0xF);
    }

    void setLightR(int32_t x, int32_t y, int32_t z, int32_t val) {
        lights[toIndex(x, y, z)] = (lights[toIndex(x, y, z)] & 0xFFF0) | ((val & 0xF) << 0);
    }

    void setLightG(int32_t x, int32_t y, int32_t z, int32_t val) {
        lights[toIndex(x, y, z)] = (lights[toIndex(x, y, z)] & 0xFF0F) | ((val & 0xF) << 4);
    }

    void setLightB(int32_t x, int32_t y, int32_t z, int32_t val) {
        lights[toIndex(x, y, z)] = (lights[toIndex(x, y, z)] & 0xF0FF) | ((val & 0xF) << 8);
    }

    void setLightS(int32_t x, int32_t y, int32_t z, int32_t val) {
        lights[toIndex(x, y, z)] = (lights[toIndex(x, y, z)] & 0x0FFF) | ((val & 0xF) << 12);
    }

    void setLight(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val) {
        switch (channel) {
            case 0: setLightR(x, y, z, val); break;
            case 1: setLightG(x, y, z, val); break;
            case 2: setLightB(x, y, z, val); break;
            case 3: setLightS(x, y, z, val); break;
        }
    }

    auto getLight(int32_t x, int32_t y, int32_t z, int32_t channel) -> int32_t {
        switch (channel) {
            case 0: return getLightR(x, y, z);
            case 1: return getLightG(x, y, z);
            case 2: return getLightB(x, y, z);
            case 3: return getLightS(x, y, z);
        }
        return 0;
    }

    auto getLightPacked(int32_t x, int32_t y, int32_t z) -> int32_t {
        return lights[toIndex(x, y, z)];
    }

private:
    static constexpr auto toIndex(int32_t x, int32_t y, int32_t z) noexcept -> size_t {
        return (y << 8) | (z << 4) | x;
    }
};

struct Chunk {
    ChunkPos pos;
	int32_t status = 0;
	bool needRender = false;

	std::array<std::unique_ptr<ChunkSection>, 16> sections{};
    std::array<std::unique_ptr<LightSection>, 16> skyLightSections{};
    std::array<std::unique_ptr<LightSection>, 16> blockLightSections{};

    std::array<std::unique_ptr<Lightmap>, 16> lightSections{};

    Heightmap heightmap{};

	RenderBuffer rb{};
	ChunkLayer layers[3]{};
    std::unique_ptr<Mesh> mesh{nullptr};

    std::vector<std::shared_ptr<StructureStart>> structureStarts;
    std::vector<std::shared_ptr<StructureStart>> structureReferences;

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
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<Lightmap>();
        }
        section->setLight(x & 15, y & 15, z & 15, channel, val);
    }

    auto getLight(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            return 0;
        }
        return section->getLight(x & 15, y & 15, z & 15, channel);
    }

    auto getLightPacked(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            return 0;
        }
        return section->getLightPacked(x & 15, y & 15, z & 15);
    }

    void setData(const BlockPos& pos, BlockData data) {
        setData(pos.x, pos.y, pos.z, data);
    }

    void setData(int32_t x, int32_t y, int32_t z, BlockData data) {
    	auto& section = sections[y >> 4];
    	if (section == nullptr) {
    	    if (data.isAir()) {
    	        return;
    	    }
    		section = std::make_unique<ChunkSection>();
    	}
        updateHeightmap(x & 15, y, z & 15, data);
    	section->blocks[toIndex(x & 15, y & 15, z & 15)] = data;
    }

    void updateHeightmap(int32_t x, int32_t y, int32_t z, BlockData data) {
        const int32_t i = x | (z << 4);
        const int32_t height = heightmap.getAt(i);

        if (y > height - 2) {
            if (!data.isAir()) {
                if (y >= height) {
                    heightmap.setAt(i, y + 1);
                }
            } else if (height - 1 == y) {
                for (int y1 = y - 1; y1 >= 0; --y1) {
                    if (!getData(x, y1, z).isAir()) {
                        heightmap.setAt(i, y1 + 1);
                        break;
                    }
                }
                heightmap.setAt(i, 0);
            }
        }
    }

    auto getData(const BlockPos& pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
    	auto& section = sections[y >> 4];
    	if (section == nullptr) {
			return {};
    	}
        return section->blocks[toIndex(x & 15, y & 15, z & 15)];
    }

    auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
        return getData(x, y, z).getBlock();
    }

    void updateMesh() {
        if (!mesh) {
            mesh = std::make_unique<Mesh>();
        }

		int32_t index_count = 0;
		for (auto& subindices : rb.indices) {
			index_count += subindices.size();
		}

        mesh->SetVertices(rb.vertices);
        mesh->SetIndicesCount(index_count);

		int32_t submesh_index = 0;
        int32_t index_offset = 0;

        for (auto& submesh : rb.indices) {
        	layers[submesh_index].index_offset = index_offset;
        	layers[submesh_index].index_count = submesh.size();
        	if (!submesh.empty()) {
				mesh->SetIndicesData(submesh, index_offset);
        	}
			index_offset += layers[submesh_index].index_count;
			submesh_index++;
        }
    }

    auto getHeight(HeightmapType type, int32_t x, int32_t z) -> int32_t {
        return heightmap.get(x, z);
    }

    auto getTopBlockY(HeightmapType type, int32_t x, int32_t z) -> int32_t {
        return getHeight(type, x, z) - 1;
    }

    static constexpr auto toIndex(int32_t x, int32_t y, int32_t z) noexcept -> int32_t {
        return (x << 8) | (z << 4) | y;
    }

    void updateHeightmaps() {
        for (int z = 0; z < 16; z++) {
            for (int x = 0; x < 16; x++) {
                const int i = x | (z << 4);

                for (int y = 255; y >= 0; y--) {
                    if (!getData(x, y, z).isAir()) {
                        heightmap.setAt(i, y + 1);
                        break;
                    }
                }
            }
        }
    }
};

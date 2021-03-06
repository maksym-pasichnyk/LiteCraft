#pragma once

#include "src/BlockTable.hpp"
#include "src/BlockReader.hpp"

#include "src/mesh.hpp"
#include "src/Block.hpp"
#include "src/util/math/ChunkPos.hpp"

#include <glm/vec3.hpp>

#include <vector>
#include <memory>
#include <cassert>
#include <queue>

struct WorldGenRegion;

struct RenderLayerBuilder {
	std::vector<Vertex>& vertices;
	std::vector<int>& indices;

	void quad() {
        auto i = vertices.size();
        indices.push_back(i + 0);
        indices.push_back(i + 2);
        indices.push_back(i + 1);
        indices.push_back(i + 0);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }
    void quadInv() {
        auto i = vertices.size();
        indices.push_back(i + 0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i + 0);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
    }

    void vertex(float x, float y, float z, float u, float v, uint8_t r, uint8_t g, uint8_t b, uint8_t light) {
        vertices.push_back(Vertex{
                .point{x, y, z},
                .tex{u, v},
                .color{r, g, b, light}
        });
    }
};

enum class RenderLayer;

struct SimpleVBuffer {
    std::vector<Vertex> vertices;
    std::vector<int32_t> indices;

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
		quad(0, 2, 1, 0, 3, 2);
    }
    void quadInv() {
		quad(0, 1, 2, 0, 2, 3);
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

enum class ChunkState {
	Empty,
	StructureStart,
	StructureReferences,
	Noise,
	Surface,
	Features,
	Light,
	Full
};

struct ChunkSection {
    std::array<BlockData, 4096> blocks;
};

struct StructureBoundingBox {
    int min_x;
    int min_y;
    int min_z;
    int max_x;
    int max_y;
    int max_z;


    constexpr bool contains(int x, int y, int z) const noexcept {
        return min_x <= x && x <= max_x &&
               min_y <= y && y <= max_y &&
               min_z <= z && z <= max_z;
    }

    constexpr bool intersect(const StructureBoundingBox& boundingBox) const noexcept {
        return min_x <= boundingBox.max_x && max_x >= boundingBox.min_x &&
               min_y <= boundingBox.max_y && max_y >= boundingBox.min_y &&
               min_z <= boundingBox.max_z && max_z >= boundingBox.min_z;
    }

    static constexpr StructureBoundingBox withSize(int x, int y, int z, int size_x, int size_y, int size_z) {
        return StructureBoundingBox{x, y, z, x + size_x - 1, y + size_y - 1, z + size_z - 1};
    }

    static constexpr StructureBoundingBox fromChunkPos(int chunk_x, int chunk_z) {
        const int pos_x = chunk_x << 4;
        const int pos_z = chunk_z << 4;

        return StructureBoundingBox{pos_x, 0, pos_z, pos_x + 15, 255, pos_z + 15};
    }
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
    StructureBoundingBox boundingBox;

    virtual ~StructurePiece() = default;

    virtual void place(WorldGenRegion& region, StructureBoundingBox bb) = 0;

    int get_x_with_offset(int x, int z) {
        switch (coordBaseMode) {
            case SOUTH:
            case NORTH:
                return boundingBox.min_x + x;
            case WEST:
                return boundingBox.max_x - z;
            case EAST:
                return boundingBox.min_x + z;
        }
        return x;
    }

    int get_y_with_offset(int y) {
        return boundingBox.min_y + y;
    }

    int get_z_with_offset(int x, int z) {
        switch (coordBaseMode) {
            case NORTH:
                return boundingBox.max_z - z;
            case SOUTH:
                return boundingBox.min_z + z;
            case WEST:
            case EAST:
                return boundingBox.min_z + x;
        }
        return z;
    }

    auto setBlock(IBlockReader auto &blocks, StructureBoundingBox sbb, int x, int y, int z, BlockData blockData) {
        glm::ivec3 blockpos{get_x_with_offset(x, z), get_y_with_offset(y), get_z_with_offset(x, z)};

        if (sbb.contains(blockpos.x, blockpos.y, blockpos.z)) {
            if (coordBaseMode == EAST || coordBaseMode == NORTH) {
                auto val = 0;
                if (blockData.val & BlockPane_WEST) {
                    val |= BlockPane_WEST;
                }
                if (blockData.val & BlockPane_NORTH) {
                    val |= BlockPane_SOUTH;
                }
                if (blockData.val & BlockPane_EAST) {
                    val |= BlockPane_EAST;
                }
                if (blockData.val & BlockPane_SOUTH) {
                    val |= BlockPane_NORTH;
                }
                blockData.val = val;
            }

            if (coordBaseMode == EAST || coordBaseMode == WEST) {
                auto val = 0;
                if (blockData.val & BlockPane_WEST) {
                    val |= BlockPane_SOUTH;
                }
                if (blockData.val & BlockPane_NORTH) {
                    val |= BlockPane_WEST;
                }
                if (blockData.val & BlockPane_EAST) {
                    val |= BlockPane_NORTH;
                }
                if (blockData.val & BlockPane_SOUTH) {
                    val |= BlockPane_EAST;
                }
                blockData.val = val;
            }

            blocks.setData(blockpos.x, blockpos.y, blockpos.z, blockData);
        }
    }
};

struct StructureStart {
    StructureBoundingBox boundingBox;
    std::vector<std::unique_ptr<StructurePiece>> pieces;

    virtual ~StructureStart() = default;
    virtual void build(int pos_x, int pos_z) = 0;

    void updateBoundingBox() {
        boundingBox.min_x = std::numeric_limits<int>::max();
        boundingBox.min_y = std::numeric_limits<int>::max();
        boundingBox.min_z = std::numeric_limits<int>::max();
        boundingBox.max_x = std::numeric_limits<int>::min();
        boundingBox.max_y = std::numeric_limits<int>::min();
        boundingBox.max_z = std::numeric_limits<int>::min();

        for (auto& piece : pieces) {
            boundingBox.min_x = std::min(boundingBox.min_x, piece->boundingBox.min_x);
            boundingBox.min_y = std::min(boundingBox.min_y, piece->boundingBox.min_y);
            boundingBox.min_z = std::min(boundingBox.min_z, piece->boundingBox.min_z);
            boundingBox.max_x = std::max(boundingBox.max_x, piece->boundingBox.max_x);
            boundingBox.max_y = std::max(boundingBox.max_y, piece->boundingBox.max_y);
            boundingBox.max_z = std::max(boundingBox.max_z, piece->boundingBox.max_z);
        }
    }
};

struct Heightmap {
    std::array<int32_t, 16 * 16> data;

    Heightmap() {
        data.fill(-1);
    }

    int32_t& operator[](size_t i) {
        return data[i];
    }

    const int32_t& operator[](size_t i) const {
        return data[i];
    }
};

struct Light {
    uint8_t block : 4;
    uint8_t sky : 4;
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

private:
    static constexpr auto toIndex(int32_t x, int32_t y, int32_t z) noexcept -> size_t {
        return (y << 8) | (z << 4) | x;
    }
};

struct Chunk {
    ChunkPos pos;
	ChunkState state = ChunkState::Empty;
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

    void setSkyLight(int32_t x, int32_t y, int32_t z, int32_t new_light) {
        auto& section = skyLightSections[y >> 4];
        if (section == nullptr) {
            if (new_light == /*15*/0) {
                return;
            }
            section = std::make_unique<LightSection>();
        }
        section->setLight(x & 15, y & 15, z & 15, /*15 -*/ new_light);
    }

    auto getSkyLight(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto& section = skyLightSections[y >> 4];
        if (section == nullptr) {
            return /*15*/0;
        }
        return /*15 - */section->getLight(x & 15, y & 15, z & 15);
    }

    void setBlockLight(int32_t x, int32_t y, int32_t z, int32_t new_light) {
        auto& section = blockLightSections[y >> 4];
        if (section == nullptr) {
            if (new_light == 0) {
                return;
            }
            section = std::make_unique<LightSection>();
        }
        section->setLight(x & 15, y & 15, z & 15, new_light);
    }

    auto getBlockLight(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto& section = blockLightSections[y >> 4];
        if (section == nullptr) {
            return 0;
        }
        return section->getLight(x & 15, y & 15, z & 15);
    }

    void setLightS(int32_t x, int32_t y, int32_t z, int32_t val) {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            if (val == 15) {
                return;
            }
            section = std::make_unique<Lightmap>();
        }
        section->setLightS(x & 15, y & 15, z & 15, 15 - val);
    }

    auto getLightS(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            return 15;
        }
        return 15 - section->getLightS(x & 15, y & 15, z & 15);
    }

    void setLightR(int32_t x, int32_t y, int32_t z, int32_t val) {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<Lightmap>();
        }
        section->setLightR(x & 15, y & 15, z & 15, val);
    }

    auto getLightR(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            return 0;
        }
        return section->getLightR(x & 15, y & 15, z & 15);
    }

    void setLightG(int32_t x, int32_t y, int32_t z, int32_t val) {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<Lightmap>();
        }
        section->setLightG(x & 15, y & 15, z & 15, val);
    }

    auto getLightG(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            return 0;
        }
        return section->getLightG(x & 15, y & 15, z & 15);
    }

    void setLightB(int32_t x, int32_t y, int32_t z, int32_t val) {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            if (val == 0) {
                return;
            }
            section = std::make_unique<Lightmap>();
        }
        section->setLightB(x & 15, y & 15, z & 15, val);
    }

    auto getLightB(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto& section = lightSections[y >> 4];
        if (section == nullptr) {
            return 0;
        }
        return section->getLightB(x & 15, y & 15, z & 15);
    }

    void setData(int32_t x, int32_t y, int32_t z, BlockData blockData) {
    	auto& section = sections[y >> 4];
    	if (section == nullptr) {
    		section = std::make_unique<ChunkSection>();
    	}
        heightmap[(x & 15) + (z & 15) * 16] = -1;
    	section->blocks[toIndex(x, y, z)] = blockData;
    }

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
    	auto& section = sections[y >> 4];
    	if (section == nullptr) {
			return {};
    	}
        return section->blocks[toIndex(x, y, z)];
    }

    auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
        return Block::id_to_block[(int) getData(x, y, z).id];
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

    auto getHeight(int32_t x, int32_t z) -> int32_t {
        const auto i = (x & 15) + (z & 15) * 16;
        if (heightmap[i] == -1) {
            for (int y = 255; y >= 0; y--) {
                if (getData(x, y, z).id != BlockID::AIR) {
                    heightmap[i] = y + 1;
                    break;
                }
            }
        }
        return heightmap[i];
    }

    auto getTopBlockY(/*type, */int32_t x, int32_t z) -> int32_t {
        return getHeight(x, z) - 1;
    }

    static constexpr auto toIndex(int32_t x, int32_t y, int32_t z) noexcept -> int32_t {
        const auto inner_x = x & 15;
        const auto inner_y = y & 15;
        const auto inner_z = z & 15;

        return (inner_x << 8) | (inner_z << 4) | inner_y;
    }
};

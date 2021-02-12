#pragma once

#include "BlockTable.hpp"
#include "BlockReader.hpp"

#include "mesh.hpp"
#include "Block.hpp"
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

    void vertex(f32 x, f32 y, f32 z, f32 u, f32 v, uint8 r, uint8 g, uint8 b, uint8_t light) {
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
    std::vector<int32> indices;

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

    void vertex(f32 x, f32 y, f32 z, f32 u, f32 v, uint8 r, uint8 g, uint8 b, uint8 a) {
        vertices.push_back(Vertex{
			.point{x, y, z},
			.tex{u, v},
			.color{r, g, b, a}
        });
    }
};

struct RenderBuffer {
    std::vector<Vertex> vertices;
    std::vector<int32> indices[3]{};

	auto getForLayer(RenderLayer layer) -> RenderLayerBuilder {
		return RenderLayerBuilder {
			.vertices = vertices,
			.indices = indices[(usize) layer]
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
	int32 index_offset = 0;
	int32 index_count = 0;
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

//struct Light {
//	int8 block : 4;
//	int8 sky   : 4;
//};

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

    virtual void place(WorldGenRegion& region, BlockTable& global_pallete, StructureBoundingBox bb) = 0;

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

//std::

#include <bitset>


struct Heightmap {
    int16_t data[16][16];

    int32_t get(int32_t x, int32_t z) {
        return data[x][z];
    }
};

struct Light {
    uint8 block : 4;
    uint8 sky : 4;
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

    auto getLight(int32_t x, int32_t y, int32_t z) const -> int32 {
        const auto idx = toIndex(x, y, z);
        const auto light = lights[idx >> 1];
        return (((idx & 1) == 1) ? (light >> 4) : light) & 0xF;
    }

private:
    static constexpr auto toIndex(int32 x, int32 y, int32 z) noexcept -> usize {
        return (y << 8) | (z << 4) | x;
    }
};

struct Chunk {
    ChunkPos pos;
	ChunkState state = ChunkState::Empty;
	bool is_dirty = false;
    bool needRender = false;
    bool needUpdate = false;

	std::array<std::unique_ptr<ChunkSection>, 16> sections{};
    std::array<std::unique_ptr<LightSection>, 16> skyLightSections{};
    std::array<std::unique_ptr<LightSection>, 16> blockLightSections{};

    std::array<int32, 16 * 16> heightmap;

	RenderBuffer rb{};
	ChunkLayer layers[3]{};
    std::unique_ptr<Mesh> mesh{nullptr};

    std::vector<std::shared_ptr<StructureStart>> structureStarts;
//    std::vector<std::weak_ptr<StructureStart>> structureReferences;

    explicit Chunk(ChunkPos pos) : pos{pos} {
        heightmap.fill(-1);
    }

    void setSkyLight(int32 x, int32 y, int32 z, int32 new_light) {
        auto& section = skyLightSections[y >> 4];
        if (section == nullptr) {
            if (new_light == 15) {
                return;
            }
            section = std::make_unique<LightSection>();
        }
        needRender = true;
        section->setLight(x & 15, y & 15, z & 15, 15 - new_light);
    }

    auto getSkyLight(int32 x, int32 y, int32 z) const -> int32 {
        auto& section = skyLightSections[y >> 4];
        if (section == nullptr) {
            return 15;
        }
        return 15 - section->getLight(x & 15, y & 15, z & 15);
    }

    void setBlockLight(int32 x, int32 y, int32 z, int32 new_light) {
        auto& section = blockLightSections[y >> 4];
        if (section == nullptr) {
            if (new_light == 0) {
                return;
            }
            section = std::make_unique<LightSection>();
        }
        section->setLight(x & 15, y & 15, z & 15, new_light);
    }

    auto getBlockLight(int32 x, int32 y, int32 z) const -> int32 {
        auto& section = blockLightSections[y >> 4];
        if (section == nullptr) {
            return 0;
        }
        return section->getLight(x & 15, y & 15, z & 15);
    }

    void setData(int32 x, int32 y, int32 z, BlockData blockData) {
    	auto& section = sections[y >> 4];
    	if (section == nullptr) {
    		section = std::make_unique<ChunkSection>();
    	}
        heightmap[(x & 15) + (z & 15) * 16] = -1;
    	section->blocks[toIndex(x, y, z)] = blockData;
    }

    auto getData(int32 x, int32 y, int32 z) const -> BlockData {
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

		int32 index_count = 0;
		for (auto& subindices : rb.indices) {
			index_count += subindices.size();
		}

        mesh->SetVertices(rb.vertices);
        mesh->SetIndicesCount(index_count);

		int32 submesh_index = 0;
        int32 index_offset = 0;

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

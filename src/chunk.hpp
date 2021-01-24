#pragma once

#include "mesh.hpp"
#include "block.hpp"

#include <glm/vec3.hpp>

#include <vector>
#include <memory>

enum class ChunkState {
	Empty,
	StructureStart,
	StructureReferences,
	Noise,
	Features,
	Light,
	Full
};

struct Light {
	int8 block : 4;
	int8 sky   : 4;
};

struct ChunkSection {
    BlockState states[16][16][16]{};
};

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

    void vertex(f32 x, f32 y, f32 z, f32 u, f32 v, uint8 r, uint8 g, uint8 b, uint8 a) {
        vertices.push_back(Vertex{
                .point{x, y, z},
                .tex{u, v},
                .color{r, g, b, a}
        });
    }
};

enum class RenderLayer;

struct VBuffer {
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

struct Chunk {
	ChunkState state = ChunkState::Empty;
	bool is_dirty = false;
    bool needRender = false;
    bool needUpdate = false;

	ChunkSection* sections[16]{};
//    Light lights[256][16][16]{};

    int32 heightmap[16][16];

	RenderBuffer rb{};
	ChunkLayer layers[3]{};
    std::unique_ptr<Mesh> mesh{nullptr};

    void setBlock(int32 x, int32 y, int32 z, BlockState blockState) {
    	auto& section = sections[y >> 4];
    	if (section == nullptr) {
    		section = new ChunkSection();
    	}
    	section->states[x & 15][y & 15][z & 15] = blockState;
    }

    auto getBlock(int32 x, int32 y, int32 z) -> BlockState {
    	auto& section = sections[y >> 4];
    	if (section == nullptr) {
			return {};
    	}
        return section->states[x & 15][y & 15][z & 15];
    }

//    void setLight(int32 x, int32 y, int32 z, Light light) {
//        lights[y][x & 15][z & 15] = light;
//    }
//
//    auto getLight(int32 x, int32 y, int32 z) -> Light {
//        return lights[y][x & 15][z & 15];
//    }

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
};

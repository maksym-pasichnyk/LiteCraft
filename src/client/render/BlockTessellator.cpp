#include "RawModels.hpp"
#include "Definition.hpp"

#include <glm/vec3.hpp>
#include <TextureAtlas.hpp>
#include <ResourceManager.hpp>

#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <block/BlockStates.hpp>
#include <block/material/Materials.hpp>

#include <client/render/RenderBuffer.hpp>
#include <client/render/chunk/ChunkRenderCache.hpp>

auto getTintColor(TintType tint) -> glm::u8vec3 {
	if (tint == TintType::Grass) {
		return {0x91, 0xBD, 0x59};
	} else if (tint == TintType::Foliage) {
		return {0x77, 0xAB, 0x2F};
	} else {
		return {0xFF, 0xFF, 0xFF};
	}
}

static auto vertexAO(int side1, int side2, int corner) -> int {
    return side1 && side2 ? 0 : (3 - (side1 + side2 + corner));
}

static auto shouldRenderFace(Block* block_a, Block* block_b) -> bool {
    if (block_a->getRenderType() != block_b->getRenderType()) {
        return true;
    }
    return block_b->getMaterial() == Materials::LEAVES;
}

void tessellate(RenderBuffer& rb, const glm::ivec3& pos, const Model& model) {
    for (auto&& quad : model.quads) {
        auto builder = rb.getForLayer(quad.layer);

        builder.quad();

        const auto texture = TextureManager::instance().get_texture(quad.texture);
        for (auto&& vertex : quad.vertices) {
            const auto [x, y, z] = vertex.pos + glm::vec3(pos);
            const auto u = texture.getInterpolatedU(vertex.uv.x);
            const auto v = texture.getInterpolatedV(vertex.uv.y);
            builder.vertex(x, y, z, u, v, 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
        }
    }
}

void renderBlocks(RenderBuffer& rb, ChunkRenderCache& blocks) {
	rb.clear();

    const auto start = blocks.coords.getStartBlock();

    for (int x = start.x; x < start.x + 16; x++) {
        for (int z = start.z; z < start.z + 16; z++) {
            for (int y = 0; y < 256; y++) {
                const auto pos = glm::ivec3{x, y, z};
                const auto state = blocks.getData(pos);
                const auto block = state.getBlock();

                if (block->getRenderType() == RenderType::Air) {
                    continue;
                }

                if (auto model = BlockStates::get(block)->get_model(state)) {
                    tessellate(rb, pos, *model);
                }
//                renderLiquid(pos, block, rb, blocks);
            }
        }
    }
}
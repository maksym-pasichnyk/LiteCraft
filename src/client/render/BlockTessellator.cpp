#include "../../block/Block.hpp"
#include "../../block/BlockGraphics.hpp"
#include "../../world/chunk/Chunk.hpp"
#include "../../BlockReader.hpp"
#include "../../TextureAtlas.hpp"
#include "ChunkRenderCache.h"

#include <glm/vec3.hpp>

auto getTintColor(Tint tint) -> glm::u8vec3 {
	if (tint == Tint::Grass) {
		return {0x91, 0xBD, 0x59};
	} else if (tint == Tint::Foliage) {
		return {0x77, 0xAB, 0x2F};
	} else {
		return {0xFF, 0xFF, 0xFF};
	}
}

int vertexAO(int side1, int side2, int corner) {
    return side1 && side2 ? 0 : (3 - (side1 + side2 + corner));
}

bool shouldRenderFace(Block* block_a, Block* block_b) {
    if (block_a->renderType != block_b->renderType) {
        return true;
    }

    return block_b->renderType == RenderType::Leaves;
}

void renderBlockWithAO(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
	const auto fx = static_cast<float>(x);
	const auto fy = static_cast<float>(y);
	const auto fz = static_cast<float>(z);

	auto [r, g, b] = getTintColor(block->tint);

	auto builder = rb.getForLayer(block->renderLayer);

	auto val = blocks.getData(x, y, z).val;

    float aoLights[4] {0.3, 0.6, 0.9, 1 };

	if (shouldRenderFace(blocks.getBlock(x, y, z - 1), block)) {
        const auto packedLight = blocks.getLightPacked(x, y, z - 1);
        const auto coords = block->graphics->southTexture->get(val);

        const auto uf = isOpaque(blocks.getData(x, y + 1, z - 1));
        const auto ub = isOpaque(blocks.getData(x, y - 1, z - 1));
        const auto ul = isOpaque(blocks.getData(x - 1, y, z - 1));
        const auto ur = isOpaque(blocks.getData(x + 1, y, z - 1));

        const int ao0 = vertexAO(ub, ul, isOpaque(blocks.getData(x - 1, y - 1, z - 1)));
        const int ao1 = vertexAO(uf, ul, isOpaque(blocks.getData(x - 1, y + 1, z - 1)));
        const int ao2 = vertexAO(uf, ur, isOpaque(blocks.getData(x + 1, y + 1, z - 1)));
        const int ao3 = vertexAO(ub, ur, isOpaque(blocks.getData(x + 1, y - 1, z - 1)));

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.7f);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.7f);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.7f);
	}

	if (shouldRenderFace(blocks.getBlock(x + 1, y, z), block)) {
        const auto packedLight = blocks.getLightPacked(x + 1, y, z);
        const auto coords = block->graphics->eastTexture->get(val);

        const auto uf = isOpaque(blocks.getData(x + 1, y - 1, z));
        const auto ub = isOpaque(blocks.getData(x + 1, y + 1, z));
        const auto ul = isOpaque(blocks.getData(x + 1, y, z + 1));
        const auto ur = isOpaque(blocks.getData(x + 1, y, z - 1));

        const int ao0 = vertexAO(uf, ur, isOpaque(blocks.getData(x + 1, y - 1, z - 1)));
        const int ao1 = vertexAO(ub, ur, isOpaque(blocks.getData(x + 1, y + 1, z - 1)));
        const int ao2 = vertexAO(ub, ul, isOpaque(blocks.getData(x + 1, y + 1, z + 1)));
        const int ao3 = vertexAO(uf, ul, isOpaque(blocks.getData(x + 1, y - 1, z + 1)));

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.8f);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.8f);
	}

	if (shouldRenderFace(blocks.getBlock(x, y, z + 1), block)) {
        const auto packedLight = blocks.getLightPacked(x, y, z + 1);
        const auto coords = block->graphics->northTexture->get(val);

        const auto uf = isOpaque(blocks.getData(x, y - 1, z + 1));
        const auto ub = isOpaque(blocks.getData(x, y + 1, z + 1));
        const auto ul = isOpaque(blocks.getData(x - 1, y, z + 1));
        const auto ur = isOpaque(blocks.getData(x + 1, y, z + 1));

        const int ao0 = vertexAO(uf, ur, isOpaque(blocks.getData(x + 1, y - 1, z + 1)));
        const int ao1 = vertexAO(ub, ur, isOpaque(blocks.getData(x + 1, y + 1, z + 1)));
        const int ao2 = vertexAO(ub, ul, isOpaque(blocks.getData(x - 1, y + 1, z + 1)));
        const int ao3 = vertexAO(uf, ul, isOpaque(blocks.getData(x - 1, y - 1, z + 1)));

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.8f);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.8f);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.8f);
	}

	if (shouldRenderFace(blocks.getBlock(x - 1, y, z), block)) {
        const auto packedLight = blocks.getLightPacked(x - 1, y, z);
        const auto coords = block->graphics->westTexture->get(val);

        const auto uf = isOpaque(blocks.getData(x - 1, y - 1, z));
        const auto ub = isOpaque(blocks.getData(x - 1, y + 1, z));
        const auto ul = isOpaque(blocks.getData(x - 1, y, z - 1));
        const auto ur = isOpaque(blocks.getData(x - 1, y, z + 1));

        const int ao0 = vertexAO(uf, ur, isOpaque(blocks.getData(x - 1, y - 1, z + 1)));
        const int ao1 = vertexAO(ub, ur, isOpaque(blocks.getData(x - 1, y + 1, z + 1)));
        const int ao2 = vertexAO(ub, ul, isOpaque(blocks.getData(x - 1, y + 1, z - 1)));
        const int ao3 = vertexAO(uf, ul, isOpaque(blocks.getData(x - 1, y - 1, z - 1)));

        builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.7f);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.7f);
	}

	if (shouldRenderFace(blocks.getBlock(x, y + 1, z), block)) {
        const auto packedLight = blocks.getLightPacked(x, y + 1, z);
		const auto coords = block->graphics->topTexture->get(val);

        const auto uf = isOpaque(blocks.getData(x, y + 1, z + 1));
        const auto ub = isOpaque(blocks.getData(x, y + 1, z - 1));
        const auto ul = isOpaque(blocks.getData(x - 1, y + 1, z));
        const auto ur = isOpaque(blocks.getData(x + 1, y + 1, z));

        const int ao0 = vertexAO(ub, ul, isOpaque(blocks.getData(x - 1, y + 1, z - 1)));
        const int ao1 = vertexAO(uf, ul, isOpaque(blocks.getData(x - 1, y + 1, z + 1)));
        const int ao2 = vertexAO(uf, ur, isOpaque(blocks.getData(x + 1, y + 1, z + 1)));
        const int ao3 = vertexAO(ub, ur, isOpaque(blocks.getData(x + 1, y + 1, z - 1)));

		builder.quad();
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 1.0f);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 1.0f);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 1.0f);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 1.0f);
	}

	if (shouldRenderFace(blocks.getBlock(x, y - 1, z), block)) {
        const auto packedLight = blocks.getLightPacked(x, y - 1, z);
        const auto coords = block->graphics->bottomTexture->get(val);

        const auto df = isOpaque(blocks.getData(x, y - 1, z + 1));
        const auto db = isOpaque(blocks.getData(x, y - 1, z - 1));
        const auto dl = isOpaque(blocks.getData(x - 1, y - 1, z));
        const auto dr = isOpaque(blocks.getData(x + 1, y - 1, z));

        const int ao0 = vertexAO(df, dl, isOpaque(blocks.getData(x - 1, y - 1, z + 1)));
        const int ao1 = vertexAO(db, dl, isOpaque(blocks.getData(x - 1, y - 1, z - 1)));
        const int ao2 = vertexAO(db, dr, isOpaque(blocks.getData(x + 1, y - 1, z - 1)));
        const int ao3 = vertexAO(df, dr, isOpaque(blocks.getData(x + 1, y - 1, z + 1)));

        if (block->tint == Tint::Grass) {
            r = 0xFF;
            g = 0xFF;
            b = 0xFF;
        }

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.7f);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.7f);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.7f);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.7f);
	}
}

void renderBlockWithoutAO(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto fx = static_cast<float>(x);
    const auto fy = static_cast<float>(y);
    const auto fz = static_cast<float>(z);

    auto [r, g, b] = getTintColor(block->tint);

    auto val = blocks.getData(x, y, z).val;

    auto builder = rb.getForLayer(block->renderLayer);

    if (shouldRenderFace(blocks.getBlock(x, y, z - 1), block)) {
        const auto packedLight = blocks.getLightPacked(x, y, z - 1);
        const auto coords = block->graphics->southTexture->get(val);

        builder.quad();
        builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, 0.7f);
    }

    if (shouldRenderFace(blocks.getBlock(x + 1, y, z), block)) {
        const auto packedLight = blocks.getLightPacked(x + 1, y, z);
        const auto coords = block->graphics->eastTexture->get(val);

        builder.quad();
        builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, 0.8f);
    }

    if (shouldRenderFace(blocks.getBlock(x, y, z + 1), block)) {
        const auto packedLight = blocks.getLightPacked(x, y, z + 1);
        const auto coords = block->graphics->northTexture->get(val);

        builder.quad();
        builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, 0.8f);
    }

    if (shouldRenderFace(blocks.getBlock(x - 1, y, z), block)) {
        const auto packedLight = blocks.getLightPacked(x - 1, y, z);
        const auto coords = block->graphics->westTexture->get(val);

        builder.quad();
        builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, 0.7f);
    }

    if (shouldRenderFace(blocks.getBlock(x, y + 1, z), block)) {
        const auto packedLight = blocks.getLightPacked(x, y + 1, z);
        const auto coords = block->graphics->topTexture->get(val);

        builder.quad();
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, 1.0f);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, 1.0f);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, 1.0f);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, 1.0f);
    }

    if (shouldRenderFace(blocks.getBlock(x, y - 1, z), block)) {
        const auto packedLight = blocks.getLightPacked(x, y - 1, z);
        const auto coords = block->graphics->bottomTexture->get(val);

        if (block->tint == Tint::Grass) {
            r = 0xFF;
            g = 0xFF;
            b = 0xFF;
        }

        builder.quad();
        builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, 0.7f);
    }
}

void renderBlock(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks, bool ao) {
    (ao ? renderBlockWithAO : renderBlockWithoutAO)(x, y, z, block, rb, blocks);
}

void renderCross(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto fx = static_cast<float>(x);
    const auto fy = static_cast<float>(y);
    const auto fz = static_cast<float>(z);

	auto coords = block->graphics->southTexture->get(0);

	auto [r, g, b] = getTintColor(block->tint);

	auto builder = rb.getForLayer(block->renderLayer);

	builder.quad();
	builder.quadInv();
	builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);

	builder.quad();
	builder.quadInv();
	builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
}

void renderLiquid(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
	const auto fx = static_cast<float>(x);
	const auto fy = static_cast<float>(y);
	const auto fz = static_cast<float>(z);

	uint8_t r = 0x44;
	uint8_t g = 0xAF;
	uint8_t b = 0xF5;
	
	if (block == Blocks::lava || block == Blocks::flowing_lava) {
        r = 0xff;
        g = 0xff;
        b = 0xff;
	}

	auto builder = rb.getForLayer(block->renderLayer);

	bool up_is_liquid = blocks.getBlock(x, y + 1, z)->renderType == RenderType::Liquid;

	if (blocks.getBlock(x, y, z - 1)->renderType == RenderType::Air) {
		auto coords = block->graphics->southTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getBlock(x + 1, y, z)->renderType == RenderType::Air) {
		auto coords = block->graphics->eastTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getBlock(x, y, z + 1)->renderType == RenderType::Air) {
		auto coords = block->graphics->northTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getBlock(x - 1, y, z)->renderType == RenderType::Air) {
		auto coords = block->graphics->westTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getBlock(x, y + 1, z)->renderType == RenderType::Air) {
		auto coords = block->graphics->topTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getBlock(x, y - 1, z)->renderType == RenderType::Air) {
		auto coords = block->graphics->bottomTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}
}

void renderBox(RenderLayerBuilder& builder, int32_t x, int32_t y, int32_t z, Block* block, glm::vec3 min, glm::vec3 max) {
    const auto fx = static_cast<float>(x);
    const auto fy = static_cast<float>(y);
    const auto fz = static_cast<float>(z);

    auto tex0 = block->graphics->southTexture->get(0);
    auto tex1 = block->graphics->eastTexture->get(0);
    auto tex2 = block->graphics->northTexture->get(0);
    auto tex3 = block->graphics->westTexture->get(0);
    auto tex4 = block->graphics->topTexture->get(0);
    auto tex5 = block->graphics->bottomTexture->get(0);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex0.getInterpolatedU(min.x), tex0.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex0.getInterpolatedU(min.x), tex0.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex0.getInterpolatedU(max.x), tex0.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex0.getInterpolatedU(max.x), tex0.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex1.getInterpolatedU(min.z), tex1.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex1.getInterpolatedU(min.z), tex1.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex1.getInterpolatedU(max.z), tex1.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex1.getInterpolatedU(max.z), tex1.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex2.getInterpolatedU(max.x), tex2.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex2.getInterpolatedU(max.x), tex2.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex2.getInterpolatedU(min.x), tex2.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex2.getInterpolatedU(min.x), tex2.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex3.getInterpolatedU(max.z), tex3.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex3.getInterpolatedU(max.z), tex3.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex3.getInterpolatedU(min.z), tex3.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex3.getInterpolatedU(min.z), tex3.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex4.getInterpolatedU(min.x), tex4.getInterpolatedV(min.z), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex4.getInterpolatedU(min.x), tex4.getInterpolatedV(max.z), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex4.getInterpolatedU(max.x), tex4.getInterpolatedV(max.z), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex4.getInterpolatedU(max.x), tex4.getInterpolatedV(min.z), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex5.getInterpolatedU(min.x), tex5.getInterpolatedV(max.z), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex5.getInterpolatedU(min.x), tex5.getInterpolatedV(min.z), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex5.getInterpolatedU(max.x), tex5.getInterpolatedV(min.z), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex5.getInterpolatedU(max.x), tex5.getInterpolatedV(max.z), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
}

void renderPane(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->renderLayer);

    auto val = blocks.getData(x, y, z).val;

    renderBox(builder, x, y, z, block, glm::vec3(0.45f, 0.0f, 0.45f), glm::vec3(0.55f, 1.0f, 0.55f));

    if (val & 1) {
        renderBox(builder, x, y, z, block, glm::vec3(0.00f, 0.0f, 0.45f), glm::vec3(0.45f, 1.0f, 0.55f));
    }
    if (val & 2) {
        renderBox(builder, x, y, z, block, glm::vec3(0.45f, 0.0f, 0.55f), glm::vec3(0.55f, 1.0f, 1.0f));
    }
    if (val & 4) {
        renderBox(builder, x, y, z, block, glm::vec3(0.55f, 0.0f, 0.45f), glm::vec3(1.0f, 1.0f, 0.55f));
    }
    if (val & 8) {
        renderBox(builder, x, y, z, block, glm::vec3(0.45f, 0.0f, 0.0f), glm::vec3(0.55f, 1.0f, 0.45f));
    }
}

void renderTorch(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->renderLayer);

    const auto fx = static_cast<float>(x);
    const auto fy = static_cast<float>(y);
    const auto fz = static_cast<float>(z);

    const glm::vec3 min{0.4375f, 0.0f, 0.4375f};
    const glm::vec3 max{0.5625f, 0.625f, 0.5625f};

    auto tex0 = block->graphics->southTexture->get(0);
    auto tex1 = block->graphics->eastTexture->get(0);
    auto tex2 = block->graphics->northTexture->get(0);
    auto tex3 = block->graphics->westTexture->get(0);
    auto tex4 = block->graphics->topTexture->get(0);
    auto tex5 = block->graphics->bottomTexture->get(0);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex0.getInterpolatedU(min.x), tex0.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex0.getInterpolatedU(min.x), tex0.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex0.getInterpolatedU(max.x), tex0.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex0.getInterpolatedU(max.x), tex0.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex1.getInterpolatedU(min.z), tex1.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex1.getInterpolatedU(min.z), tex1.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex1.getInterpolatedU(max.z), tex1.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex1.getInterpolatedU(max.z), tex1.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex2.getInterpolatedU(max.x), tex2.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex2.getInterpolatedU(max.x), tex2.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex2.getInterpolatedU(min.x), tex2.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex2.getInterpolatedU(min.x), tex2.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex3.getInterpolatedU(max.z), tex3.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex3.getInterpolatedU(max.z), tex3.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex3.getInterpolatedU(min.z), tex3.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex3.getInterpolatedU(min.z), tex3.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex4.getInterpolatedU(min.x), tex4.getInterpolatedV(0.5f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex4.getInterpolatedU(min.x), tex4.getInterpolatedV(0.625f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex4.getInterpolatedU(max.x), tex4.getInterpolatedV(0.625f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex4.getInterpolatedU(max.x), tex4.getInterpolatedV(0.5f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex5.getInterpolatedU(min.x), tex5.getInterpolatedV(0.125f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex5.getInterpolatedU(min.x), tex5.getInterpolatedV(0.0f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex5.getInterpolatedU(max.x), tex5.getInterpolatedV(0.0f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex5.getInterpolatedU(max.x), tex5.getInterpolatedV(0.125f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
}

void renderBlocks(RenderBuffer& rb, ChunkRenderCache& blocks) {
	rb.clear();

	int32_t start_x = blocks.chunk_x << 4;
	int32_t start_z = blocks.chunk_z << 4;

    for (int32_t x = start_x; x < start_x + 16; x++) {
        for (int32_t z = start_z; z < start_z + 16; z++) {
            for (int32_t y = 0; y < 256; y++) {
                auto block = blocks.getBlock(x, y, z);

				switch (block->renderType) {
                case RenderType::Air:
                	break;
                case RenderType::Block:
                    renderBlock(x, y, z, block, rb, blocks, true);
                    break;
                case RenderType::Leaves:
                	renderBlock(x, y, z, block, rb, blocks, false);
                	break;
                case RenderType::Cross:
                	renderCross(x, y, z, block, rb, blocks);
                	break;
                case RenderType::Liquid:
                	renderLiquid(x, y, z, block, rb, blocks);
                    break;
                case RenderType::Pane:
                    renderPane(x, y, z, block, rb, blocks);
					break;
                case RenderType::Torch:
                    renderTorch(x, y, z, block, rb, blocks);
                    break;
				}
            }
        }
    }
}
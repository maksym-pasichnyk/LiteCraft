#include "Block.hpp"
#include "world/chunk/Chunk.hpp"
#include "BlockReader.hpp"
#include "TextureAtlas.hpp"
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

void renderBlockWithAO(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
	const auto fx = static_cast<float>(x);
	const auto fy = static_cast<float>(y);
	const auto fz = static_cast<float>(z);

	auto [r, g, b] = getTintColor(block->tint);

	auto builder = rb.getForLayer(block->renderLayer);

    float aoLights[4] {0.3, 0.6, 0.9, 1 };

	if (blocks.getBlock(x, y, z - 1)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x, y, z - 1);
        const auto coords = block->graphics->southTexture->get(0);

        auto uf = blocks.getData(x, y + 1, z - 1).id != BlockID::AIR;
        auto ub = blocks.getData(x, y - 1, z - 1).id != BlockID::AIR;
        auto ul = blocks.getData(x - 1, y, z - 1).id != BlockID::AIR;
        auto ur = blocks.getData(x + 1, y, z - 1).id != BlockID::AIR;

        const int ao0 = vertexAO(ub, ul, blocks.getData(x - 1, y - 1, z - 1).id != BlockID::AIR);
        const int ao1 = vertexAO(uf, ul, blocks.getData(x - 1, y + 1, z - 1).id != BlockID::AIR);
        const int ao2 = vertexAO(uf, ur, blocks.getData(x + 1, y + 1, z - 1).id != BlockID::AIR);
        const int ao3 = vertexAO(ub, ur, blocks.getData(x + 1, y - 1, z - 1).id != BlockID::AIR);

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, int(skyLight * aoLights[ao0] * 0.7) << 4);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, int(skyLight * aoLights[ao1] * 0.7) << 4);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, int(skyLight * aoLights[ao2] * 0.7) << 4);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, int(skyLight * aoLights[ao3] * 0.7) << 4);
	}

	if (blocks.getBlock(x + 1, y, z)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x + 1, y, z);
        const auto coords = block->graphics->eastTexture->get(0);

        auto uf = blocks.getData(x + 1, y - 1, z).id != BlockID::AIR;
        auto ub = blocks.getData(x + 1, y + 1, z).id != BlockID::AIR;
        auto ul = blocks.getData(x + 1, y, z + 1).id != BlockID::AIR;
        auto ur = blocks.getData(x + 1, y, z - 1).id != BlockID::AIR;

        const int ao0 = vertexAO(uf, ur, blocks.getData(x + 1, y - 1, z - 1).id != BlockID::AIR);
        const int ao1 = vertexAO(ub, ur, blocks.getData(x + 1, y + 1, z - 1).id != BlockID::AIR);
        const int ao2 = vertexAO(ub, ul, blocks.getData(x + 1, y + 1, z + 1).id != BlockID::AIR);
        const int ao3 = vertexAO(uf, ul, blocks.getData(x + 1, y - 1, z + 1).id != BlockID::AIR);

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, int(skyLight * aoLights[ao0] * 0.8) << 4);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, int(skyLight * aoLights[ao1] * 0.8) << 4);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, int(skyLight * aoLights[ao2] * 0.8) << 4);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, int(skyLight * aoLights[ao3] * 0.8) << 4);
	}

	if (blocks.getBlock(x, y, z + 1)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x, y, z + 1);
        const auto coords = block->graphics->northTexture->get(0);

        auto uf = blocks.getData(x, y - 1, z + 1).id != BlockID::AIR;
        auto ub = blocks.getData(x, y + 1, z + 1).id != BlockID::AIR;
        auto ul = blocks.getData(x - 1, y, z + 1).id != BlockID::AIR;
        auto ur = blocks.getData(x + 1, y, z + 1).id != BlockID::AIR;

        const int ao0 = vertexAO(uf, ur, blocks.getData(x + 1, y - 1, z + 1).id != BlockID::AIR);
        const int ao1 = vertexAO(ub, ur, blocks.getData(x + 1, y + 1, z + 1).id != BlockID::AIR);
        const int ao2 = vertexAO(ub, ul, blocks.getData(x - 1, y + 1, z + 1).id != BlockID::AIR);
        const int ao3 = vertexAO(uf, ul, blocks.getData(x - 1, y - 1, z + 1).id != BlockID::AIR);

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, int(skyLight * aoLights[ao0] * 0.8) << 4);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, int(skyLight * aoLights[ao1] * 0.8) << 4);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, int(skyLight * aoLights[ao2] * 0.8) << 4);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, int(skyLight * aoLights[ao3] * 0.8) << 4);
	}

	if (blocks.getBlock(x - 1, y, z)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x - 1, y, z);
        const auto coords = block->graphics->westTexture->get(0);

        auto uf = blocks.getData(x - 1, y - 1, z).id != BlockID::AIR;
        auto ub = blocks.getData(x - 1, y + 1, z).id != BlockID::AIR;
        auto ul = blocks.getData(x - 1, y, z - 1).id != BlockID::AIR;
        auto ur = blocks.getData(x - 1, y, z + 1).id != BlockID::AIR;

        const int ao0 = vertexAO(uf, ur, blocks.getData(x - 1, y - 1, z + 1).id != BlockID::AIR);
        const int ao1 = vertexAO(ub, ur, blocks.getData(x - 1, y + 1, z + 1).id != BlockID::AIR);
        const int ao2 = vertexAO(ub, ul, blocks.getData(x - 1, y + 1, z - 1).id != BlockID::AIR);
        const int ao3 = vertexAO(uf, ul, blocks.getData(x - 1, y - 1, z - 1).id != BlockID::AIR);

        builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, int(skyLight * aoLights[ao0] * 0.7) << 4);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, int(skyLight * aoLights[ao1] * 0.7) << 4);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, int(skyLight * aoLights[ao2] * 0.7) << 4);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, int(skyLight * aoLights[ao3] * 0.7) << 4);
	}

	if (blocks.getBlock(x, y + 1, z)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x, y + 1, z);
		const auto coords = block->graphics->topTexture->get(0);

        auto uf = blocks.getData(x, y + 1, z + 1).id != BlockID::AIR;
        auto ub = blocks.getData(x, y + 1, z - 1).id != BlockID::AIR;
        auto ul = blocks.getData(x - 1, y + 1, z).id != BlockID::AIR;
        auto ur = blocks.getData(x + 1, y + 1, z).id != BlockID::AIR;

        const int ao0 = vertexAO(ub, ul, blocks.getData(x - 1, y + 1, z - 1).id != BlockID::AIR);
        const int ao1 = vertexAO(uf, ul, blocks.getData(x - 1, y + 1, z + 1).id != BlockID::AIR);
        const int ao2 = vertexAO(uf, ur, blocks.getData(x + 1, y + 1, z + 1).id != BlockID::AIR);
        const int ao3 = vertexAO(ub, ur, blocks.getData(x + 1, y + 1, z - 1).id != BlockID::AIR);

		builder.quad();
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.minV, r, g, b, int(skyLight * aoLights[ao0] * 1.0) << 4);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, int(skyLight * aoLights[ao1] * 1.0) << 4);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, int(skyLight * aoLights[ao2] * 1.0) << 4);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.minV, r, g, b, int(skyLight * aoLights[ao3] * 1.0) << 4);
	}

	if (blocks.getBlock(x, y - 1, z)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x, y - 1, z);
        const auto coords = block->graphics->bottomTexture->get(0);

        auto df = blocks.getData(x, y - 1, z + 1).id != BlockID::AIR;
        auto db = blocks.getData(x, y - 1, z - 1).id != BlockID::AIR;
        auto dl = blocks.getData(x - 1, y - 1, z).id != BlockID::AIR;
        auto dr = blocks.getData(x + 1, y - 1, z).id != BlockID::AIR;

        const int ao0 = vertexAO(df, dl, blocks.getData(x - 1, y - 1, z + 1).id != BlockID::AIR);
        const int ao1 = vertexAO(db, dl, blocks.getData(x - 1, y - 1, z - 1).id != BlockID::AIR);
        const int ao2 = vertexAO(db, dr, blocks.getData(x + 1, y - 1, z - 1).id != BlockID::AIR);
        const int ao3 = vertexAO(df, dr, blocks.getData(x + 1, y - 1, z + 1).id != BlockID::AIR);

        if (block->tint == Tint::Grass) {
            r = 0xFF;
            g = 0xFF;
            b = 0xFF;
        }

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, int(skyLight * aoLights[ao0] * 0.7) << 4);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, int(skyLight * aoLights[ao1] * 0.7) << 4);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, int(skyLight * aoLights[ao2] * 0.7) << 4);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, int(skyLight * aoLights[ao3] * 0.7) << 4);
	}
}

void renderBlockWithoutAO(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto fx = float(x);
    const auto fy = float(y);
    const auto fz = float(z);

    auto [r, g, b] = getTintColor(block->tint);

    auto builder = rb.getForLayer(block->renderLayer);

    if (blocks.getBlock(x, y, z - 1)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x, y, z - 1);
        const auto coords = block->graphics->southTexture->get(0);

        builder.quad();
        builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, int(skyLight * 0.7) << 4);
    }

    if (blocks.getBlock(x + 1, y, z)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x + 1, y, z);
        const auto coords = block->graphics->eastTexture->get(0);

        builder.quad();
        builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, int(skyLight * 0.8) << 4);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, int(skyLight * 0.8) << 4);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, int(skyLight * 0.8) << 4);
        builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, int(skyLight * 0.8) << 4);
    }

    if (blocks.getBlock(x, y, z + 1)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x, y, z + 1);
        const auto coords = block->graphics->northTexture->get(0);

        builder.quad();
        builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, int(skyLight * 0.8) << 4);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, int(skyLight * 0.8) << 4);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, int(skyLight * 0.8) << 4);
        builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, int(skyLight * 0.8) << 4);
    }

    if (blocks.getBlock(x - 1, y, z)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x - 1, y, z);
        const auto coords = block->graphics->westTexture->get(0);

        builder.quad();
        builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, int(skyLight * 0.7) << 4);
    }

    if (blocks.getBlock(x, y + 1, z)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x, y + 1, z);
        const auto coords = block->graphics->topTexture->get(0);

        builder.quad();
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.minV, r, g, b, int(skyLight * 1.0) << 4);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, int(skyLight * 1.0) << 4);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, int(skyLight * 1.0) << 4);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.minV, r, g, b, int(skyLight * 1.0) << 4);
    }

    if (blocks.getBlock(x, y - 1, z)->renderType != block->renderType) {
        const auto skyLight = blocks.getSkyLight(x, y - 1, z);
        const auto coords = block->graphics->bottomTexture->get(0);

        if (block->tint == Tint::Grass) {
            r = 0xFF;
            g = 0xFF;
            b = 0xFF;
        }

        builder.quad();
        builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, int(skyLight * 0.7) << 4);
        builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, int(skyLight * 0.7) << 4);
    }
}

void renderBlock(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks, bool ao) {
    (ao ? renderBlockWithAO : renderBlockWithoutAO)(x, y, z, block, rb, blocks);
}

void renderCross(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
	const auto fx = float(x);
	const auto fy = float(y);
	const auto fz = float(z);

	auto coords = block->graphics->southTexture->get(0);

	auto [r, g, b] = getTintColor(block->tint);

	auto builder = rb.getForLayer(block->renderLayer);

	builder.quad();
	builder.quadInv();
	builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
	builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
	builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
	builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);

	builder.quad();
	builder.quadInv();
	builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
	builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
	builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
	builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
}

void renderLiquid(int32_t x, int32_t y, int32_t z, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
	const auto fx = static_cast<float>(x);// - 0.2f;
	const auto fy = static_cast<float>(y);// - 0.2f;
	const auto fz = static_cast<float>(z);// - 0.2f;

	uint8_t r = 0x44;
	uint8_t g = 0xAF;
	uint8_t b = 0xF5;

	auto builder = rb.getForLayer(block->renderLayer);

	bool up_is_liquid = blocks.getBlock(x, y + 1, z)->renderType == RenderType::Liquid;

	if (blocks.getBlock(x, y, z - 1)->renderType == RenderType::Air) {
		auto coords = block->graphics->southTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x + 1, y, z)->renderType == RenderType::Air) {
		auto coords = block->graphics->eastTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x, y, z + 1)->renderType == RenderType::Air) {
		auto coords = block->graphics->northTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x - 1, y, z)->renderType == RenderType::Air) {
		auto coords = block->graphics->westTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 255 || blocks.getBlock(x, y + 1, z)->renderType == RenderType::Air) {
		auto coords = block->graphics->topTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;


		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 0 || blocks.getBlock(x, y - 1, z)->renderType == RenderType::Air) {
		auto coords = block->graphics->bottomTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}
}

void renderBox(RenderLayerBuilder& builder, int32_t x, int32_t y, int32_t z, Block* block, glm::vec3 min, glm::vec3 max) {
    const auto fx = static_cast<float>(x);
    const auto fy = static_cast<float>(y);
    const auto fz = static_cast<float>(z);

    auto coords = block->graphics->southTexture->get(0);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, coords.minU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, coords.minU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, coords.maxU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, coords.maxU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, coords.minU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, coords.minU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, coords.maxU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, coords.maxU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, coords.minU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, coords.minU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, coords.maxU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, coords.maxU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, coords.minU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, coords.minU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, coords.maxU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, coords.maxU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);

    builder.quad();
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, coords.minU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, coords.minU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, coords.maxU, coords.maxV, 0xFF, 0xFF, 0xFF, 0xFF);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, coords.maxU, coords.minV, 0xFF, 0xFF, 0xFF, 0xFF);
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
				}
            }
        }
    }
}
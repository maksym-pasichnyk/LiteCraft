#include "ChunkRenderCache.hpp"
#include "../../block/Block.hpp"
#include "../../block/BlockGraphics.hpp"
#include "../../block/material/Materials.hpp"
#include "../../TextureAtlas.hpp"

#include <glm/vec3.hpp>

auto getTintColor(TintType tint) -> glm::u8vec3 {
	if (tint == TintType::Grass) {
		return {0x91, 0xBD, 0x59};
	} else if (tint == TintType::Foliage) {
		return {0x77, 0xAB, 0x2F};
	} else {
		return {0xFF, 0xFF, 0xFF};
	}
}

int vertexAO(int side1, int side2, int corner) {
    return side1 && side2 ? 0 : (3 - (side1 + side2 + corner));
}

bool shouldRenderFace(Block* block_a, Block* block_b) {
    if (block_a->getRenderType() != block_b->getRenderType()) {
        return true;
    }
    return block_b->getMaterial() == Materials::LEAVES;
}

void renderBlockWithAO(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto [ix, iy, iz] = pos;
    const auto [fx, fy, fz] = glm::vec3(pos);

	auto [r, g, b] = getTintColor(block->getTintType());

	auto builder = rb.getForLayer(block->getRenderLayer());

    auto& graphics = block->getGraphics();
	auto val = blocks.getData(ix, iy, iz).dv;

    float aoLights[4] {0.3, 0.6, 0.9, 1 };

	if (shouldRenderFace(blocks.getBlock(ix, iy, iz - 1), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy, iz - 1);
        const auto coords = graphics.southTexture->get(val);

        const auto uf = blocks.getData(ix, iy + 1, iz - 1).isSolid();
        const auto ub = blocks.getData(ix, iy - 1, iz - 1).isSolid();
        const auto ul = blocks.getData(ix - 1, iy, iz - 1).isSolid();
        const auto ur = blocks.getData(ix + 1, iy, iz - 1).isSolid();

        const int ao0 = vertexAO(ub, ul, blocks.getData(ix - 1, iy - 1, iz - 1).isSolid());
        const int ao1 = vertexAO(uf, ul, blocks.getData(ix - 1, iy + 1, iz - 1).isSolid());
        const int ao2 = vertexAO(uf, ur, blocks.getData(ix + 1, iy + 1, iz - 1).isSolid());
        const int ao3 = vertexAO(ub, ur, blocks.getData(ix + 1, iy - 1, iz - 1).isSolid());

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.7f);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.7f);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.7f);
	}

	if (shouldRenderFace(blocks.getBlock(ix + 1, iy, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix + 1, iy, iz);
        const auto coords = graphics.eastTexture->get(val);

        const auto uf = blocks.getData(ix + 1, iy - 1, iz).isSolid();
        const auto ub = blocks.getData(ix + 1, iy + 1, iz).isSolid();
        const auto ul = blocks.getData(ix + 1, iy, iz + 1).isSolid();
        const auto ur = blocks.getData(ix + 1, iy, iz - 1).isSolid();

        const int ao0 = vertexAO(uf, ur, blocks.getData(ix + 1, iy - 1, iz - 1).isSolid());
        const int ao1 = vertexAO(ub, ur, blocks.getData(ix + 1, iy + 1, iz - 1).isSolid());
        const int ao2 = vertexAO(ub, ul, blocks.getData(ix + 1, iy + 1, iz + 1).isSolid());
        const int ao3 = vertexAO(uf, ul, blocks.getData(ix + 1, iy - 1, iz + 1).isSolid());

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.8f);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.8f);
	}

	if (shouldRenderFace(blocks.getBlock(ix, iy, iz + 1), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy, iz + 1);
        const auto coords = graphics.northTexture->get(val);

        const auto uf = blocks.getData(ix, iy - 1, iz + 1).isSolid();
        const auto ub = blocks.getData(ix, iy + 1, iz + 1).isSolid();
        const auto ul = blocks.getData(ix - 1, iy, iz + 1).isSolid();
        const auto ur = blocks.getData(ix + 1, iy, iz + 1).isSolid();

        const int ao0 = vertexAO(uf, ur, blocks.getData(ix + 1, iy - 1, iz + 1).isSolid());
        const int ao1 = vertexAO(ub, ur, blocks.getData(ix + 1, iy + 1, iz + 1).isSolid());
        const int ao2 = vertexAO(ub, ul, blocks.getData(ix - 1, iy + 1, iz + 1).isSolid());
        const int ao3 = vertexAO(uf, ul, blocks.getData(ix - 1, iy - 1, iz + 1).isSolid());

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.8f);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.8f);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.8f);
	}

	if (shouldRenderFace(blocks.getBlock(ix - 1, iy, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix - 1, iy, iz);
        const auto coords = graphics.westTexture->get(val);

        const auto uf = blocks.getData(ix - 1, iy - 1, iz).isSolid();
        const auto ub = blocks.getData(ix - 1, iy + 1, iz).isSolid();
        const auto ul = blocks.getData(ix - 1, iy, iz - 1).isSolid();
        const auto ur = blocks.getData(ix - 1, iy, iz + 1).isSolid();

        const int ao0 = vertexAO(uf, ur, blocks.getData(ix - 1, iy - 1, iz + 1).isSolid());
        const int ao1 = vertexAO(ub, ur, blocks.getData(ix - 1, iy + 1, iz + 1).isSolid());
        const int ao2 = vertexAO(ub, ul, blocks.getData(ix - 1, iy + 1, iz - 1).isSolid());
        const int ao3 = vertexAO(uf, ul, blocks.getData(ix - 1, iy - 1, iz - 1).isSolid());

        builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.7f);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.7f);
	}

	if (shouldRenderFace(blocks.getBlock(ix, iy + 1, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy + 1, iz);
		const auto coords = graphics.topTexture->get(val);

        const auto uf = blocks.getData(ix, iy + 1, iz + 1).isSolid();
        const auto ub = blocks.getData(ix, iy + 1, iz - 1).isSolid();
        const auto ul = blocks.getData(ix - 1, iy + 1, iz).isSolid();
        const auto ur = blocks.getData(ix + 1, iy + 1, iz).isSolid();

        const int ao0 = vertexAO(ub, ul, blocks.getData(ix - 1, iy + 1, iz - 1).isSolid());
        const int ao1 = vertexAO(uf, ul, blocks.getData(ix - 1, iy + 1, iz + 1).isSolid());
        const int ao2 = vertexAO(uf, ur, blocks.getData(ix + 1, iy + 1, iz + 1).isSolid());
        const int ao3 = vertexAO(ub, ur, blocks.getData(ix + 1, iy + 1, iz - 1).isSolid());

		builder.quad();
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 1.0f);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 1.0f);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 1.0f);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 1.0f);
	}

	if (shouldRenderFace(blocks.getBlock(ix, iy - 1, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy - 1, iz);
        const auto coords = graphics.bottomTexture->get(val);

        const auto df = blocks.getData(ix, iy - 1, iz + 1).isSolid();
        const auto db = blocks.getData(ix, iy - 1, iz - 1).isSolid();
        const auto dl = blocks.getData(ix - 1, iy - 1, iz).isSolid();
        const auto dr = blocks.getData(ix + 1, iy - 1, iz).isSolid();

        const int ao0 = vertexAO(df, dl, blocks.getData(ix - 1, iy - 1, iz + 1).isSolid());
        const int ao1 = vertexAO(db, dl, blocks.getData(ix - 1, iy - 1, iz - 1).isSolid());
        const int ao2 = vertexAO(db, dr, blocks.getData(ix + 1, iy - 1, iz - 1).isSolid());
        const int ao3 = vertexAO(df, dr, blocks.getData(ix + 1, iy - 1, iz + 1).isSolid());

        if (block->getTintType() == TintType::Grass) {
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

void renderBlockWithoutAO(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto [ix, iy, iz] = pos;
    const auto [fx, fy, fz] = glm::vec3(pos);
    auto [r, g, b] = getTintColor(block->getTintType());

    auto& graphics = block->getGraphics();
    auto val = blocks.getData(ix, iy, iz).dv;

    auto builder = rb.getForLayer(block->getRenderLayer());

    if (shouldRenderFace(blocks.getBlock(ix, iy, iz - 1), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy, iz - 1);
        const auto coords = graphics.southTexture->get(val);

        builder.quad();
        builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, 0.7f);
    }

    if (shouldRenderFace(blocks.getBlock(ix + 1, iy, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix + 1, iy, iz);
        const auto coords = graphics.eastTexture->get(val);

        builder.quad();
        builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, 0.8f);
    }

    if (shouldRenderFace(blocks.getBlock(ix, iy, iz + 1), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy, iz + 1);
        const auto coords = graphics.northTexture->get(val);

        builder.quad();
        builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, 0.8f);
        builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, 0.8f);
    }

    if (shouldRenderFace(blocks.getBlock(ix - 1, iy, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix - 1, iy, iz);
        const auto coords = graphics.westTexture->get(val);

        builder.quad();
        builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, 0.7f);
        builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, 0.7f);
    }

    if (shouldRenderFace(blocks.getBlock(ix, iy + 1, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy + 1, iz);
        const auto coords = graphics.topTexture->get(val);

        builder.quad();
        builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, 1.0f);
        builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, 1.0f);
        builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, 1.0f);
        builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, 1.0f);
    }

    if (shouldRenderFace(blocks.getBlock(ix, iy - 1, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy - 1, iz);
        const auto coords = graphics.bottomTexture->get(val);

        if (block->getTintType() == TintType::Grass) {
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

void renderBlock(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks, bool ao) {
    (ao ? renderBlockWithAO : renderBlockWithoutAO)(pos, block, rb, blocks);
}

void renderCross(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto [fx, fy, fz] = glm::vec3(pos);

    auto& graphics = block->getGraphics();
	auto coords = graphics.southTexture->get(0);

	auto [r, g, b] = getTintColor(block->getTintType());

	auto builder = rb.getForLayer(block->getRenderLayer());

	constexpr float f = 0.146446609f;
	constexpr float s = 0.853553391f;

	builder.quad();
	builder.quadInv();
	builder.vertex(fx + f, fy + 0, fz + f, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + f, fy + 1, fz + f, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + s, fy + 1, fz + s, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + s, fy + 0, fz + s, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);

	builder.quad();
	builder.quadInv();
	builder.vertex(fx + f, fy + 0, fz + s, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + f, fy + 1, fz + s, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + s, fy + 1, fz + f, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
	builder.vertex(fx + s, fy + 0, fz + f, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
}

void renderLiquid(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto [ix, iy, iz] = pos;
    const auto [fx, fy, fz] = glm::vec3(pos);

    auto& graphics = block->getGraphics();
    auto material = block->getMaterial();

    uint8_t r = 0xff;
    uint8_t g = 0xff;
    uint8_t b = 0xff;
	if (material == Materials::WATER) {
        r = 0x44;
        g = 0xAF;
        b = 0xF5;
    }
	auto builder = rb.getForLayer(block->getRenderLayer());

	const bool up_is_liquid = material == blocks.getBlock(ix, iy + 1, iz)->getMaterial();

	if (blocks.getData(ix, iy, iz - 1).isAir()) {
		auto coords = graphics.southTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getData(ix + 1, iy, iz).isAir()) {
		auto coords = graphics.eastTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getData(ix, iy, iz + 1).isAir()) {
		auto coords = graphics.northTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getData(ix - 1, iy, iz).isAir()) {
		auto coords = graphics.westTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getData(ix, iy + 1, iz).isAir()) {
		auto coords = graphics.topTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}

	if (blocks.getData(ix, iy - 1, iz).isAir()) {
		auto coords = graphics.bottomTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFFFF, 1.0f);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFFFF, 1.0f);
	}
}

void renderBox(RenderLayerBuilder& builder, const glm::ivec3& pos, BlockGraphics& graphics, glm::vec3 min, glm::vec3 max) {
    const auto [fx, fy, fz] = glm::vec3(pos);

    auto tex0 = graphics.southTexture->get(0);
    auto tex1 = graphics.eastTexture->get(0);
    auto tex2 = graphics.northTexture->get(0);
    auto tex3 = graphics.westTexture->get(0);
    auto tex4 = graphics.topTexture->get(0);
    auto tex5 = graphics.bottomTexture->get(0);

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

void renderPane(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());

    auto val = blocks.getData(pos).dv;

    auto& graphics = block->getGraphics();

    renderBox(builder, pos, graphics, glm::vec3(0.45f, 0.0f, 0.45f), glm::vec3(0.55f, 1.0f, 0.55f));

    if (val & 1) {
        renderBox(builder, pos, graphics, glm::vec3(0.00f, 0.0f, 0.45f), glm::vec3(0.45f, 1.0f, 0.55f));
    }
    if (val & 2) {
        renderBox(builder, pos, graphics, glm::vec3(0.45f, 0.0f, 0.55f), glm::vec3(0.55f, 1.0f, 1.0f));
    }
    if (val & 4) {
        renderBox(builder, pos, graphics, glm::vec3(0.55f, 0.0f, 0.45f), glm::vec3(1.0f, 1.0f, 0.55f));
    }
    if (val & 8) {
        renderBox(builder, pos, graphics, glm::vec3(0.45f, 0.0f, 0.0f), glm::vec3(0.55f, 1.0f, 0.45f));
    }
}

void renderTorch(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto [fx, fy, fz] = glm::vec3(pos);
    auto builder = rb.getForLayer(block->getRenderLayer());

    const glm::vec3 min{0.4375f, 0.0f, 0.4375f};
    const glm::vec3 max{0.5625f, 0.625f, 0.5625f};

    auto& graphics = block->getGraphics();

    auto tex0 = graphics.southTexture->get(0);
    auto tex1 = graphics.eastTexture->get(0);
    auto tex2 = graphics.northTexture->get(0);
    auto tex3 = graphics.westTexture->get(0);
    auto tex4 = graphics.topTexture->get(0);
    auto tex5 = graphics.bottomTexture->get(0);

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

void renderSnow(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
//    renderBlockWithAO(pos, block, rb, blocks);
    const auto [fx, fy, fz] = glm::vec3(pos);
    auto builder = rb.getForLayer(block->getRenderLayer());

    const glm::vec3 min{0.0f, 0.0f, 0.0};
    const glm::vec3 max{1.0f, 0.125f, 1.0f};

    auto& graphics = block->getGraphics();

    renderBox(builder, pos, graphics, min, max);
}

void renderCactus(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto [fx, fy, fz] = glm::vec3(pos);
    auto builder = rb.getForLayer(block->getRenderLayer());

//    const glm::vec3 min{0.0625f, 0.0f, 0.0625f};
//    const glm::vec3 max{0.9375f, 1.0f, 0.9375f};
    const glm::vec3 min{0.0f, 0.0f, 0.0f};
    const glm::vec3 max{1.0f, 1.0f, 1.0f};

    auto& graphics = block->getGraphics();

    auto tex0 = graphics.southTexture->get(0);
    auto tex1 = graphics.eastTexture->get(0);
    auto tex2 = graphics.northTexture->get(0);
    auto tex3 = graphics.westTexture->get(0);
    auto tex4 = graphics.topTexture->get(0);
    auto tex5 = graphics.bottomTexture->get(0);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + 0.0625f, tex0.getInterpolatedU(min.x), tex0.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + 0.0625f, tex0.getInterpolatedU(min.x), tex0.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + 0.0625f, tex0.getInterpolatedU(max.x), tex0.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + 0.0625f, tex0.getInterpolatedU(max.x), tex0.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + 0.9375f, fy + min.y, fz + min.z, tex1.getInterpolatedU(min.z), tex1.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + 0.9375f, fy + max.y, fz + min.z, tex1.getInterpolatedU(min.z), tex1.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + 0.9375f, fy + max.y, fz + max.z, tex1.getInterpolatedU(max.z), tex1.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + 0.9375f, fy + min.y, fz + max.z, tex1.getInterpolatedU(max.z), tex1.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + 0.9375f, tex2.getInterpolatedU(min.x), tex2.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + 0.9375f, tex2.getInterpolatedU(min.x), tex2.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + 0.9375f, tex2.getInterpolatedU(max.x), tex2.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + 0.9375f, tex2.getInterpolatedU(max.x), tex2.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + 0.0625f, fy + min.y, fz + max.z, tex3.getInterpolatedU(min.z), tex3.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + 0.0625f, fy + max.y, fz + max.z, tex3.getInterpolatedU(min.z), tex3.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + 0.0625f, fy + max.y, fz + min.z, tex3.getInterpolatedU(max.z), tex3.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + 0.0625f, fy + min.y, fz + min.z, tex3.getInterpolatedU(max.z), tex3.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

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

void renderBambooStem(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();

    const auto [fx, fy, fz] = glm::vec3(pos);

    auto tex0 = graphics.northTexture->get(0);
    auto tex1 = tex0;//graphics.eastTexture->get(0);
    auto tex2 = tex0;//graphics.northTexture->get(0);
    auto tex3 = tex0;//graphics.westTexture->get(0);
    auto tex4 = tex0;//graphics.topTexture->get(0);
    auto tex5 = tex0;//graphics.bottomTexture->get(0);

    const glm::vec3 min{0.40625f, 0.0f, 0.40625f};
    const glm::vec3 max{0.59375f, 1.0f, 0.59375f};

    constexpr std::array uvs {
        glm::vec2{0.0f, 0.1875},
        glm::vec2{0.1875f, 0.375f},
        glm::vec2{0.375f, 0.5625},
        glm::vec2{0.5625f, 0.75f},
    };

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex0.getInterpolatedU(uvs[0].x), tex0.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex0.getInterpolatedU(uvs[0].x), tex0.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex0.getInterpolatedU(uvs[0].y), tex0.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex0.getInterpolatedU(uvs[0].y), tex0.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex1.getInterpolatedU(uvs[0].x), tex1.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex1.getInterpolatedU(uvs[0].x), tex1.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex1.getInterpolatedU(uvs[0].y), tex1.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex1.getInterpolatedU(uvs[0].y), tex1.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex2.getInterpolatedU(uvs[0].y), tex2.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex2.getInterpolatedU(uvs[0].y), tex2.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex2.getInterpolatedU(uvs[0].x), tex2.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex2.getInterpolatedU(uvs[0].x), tex2.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex3.getInterpolatedU(uvs[0].y), tex3.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex3.getInterpolatedU(uvs[0].y), tex3.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex3.getInterpolatedU(uvs[0].x), tex3.getInterpolatedV(max.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex3.getInterpolatedU(uvs[0].x), tex3.getInterpolatedV(min.y), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + max.y, fz + min.z, tex4.getInterpolatedU(0.8125f), tex4.getInterpolatedV(0.8125f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + max.y, fz + max.z, tex4.getInterpolatedU(0.8125f), tex4.getInterpolatedV(1.0f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + max.z, tex4.getInterpolatedU(1.0f), tex4.getInterpolatedV(1.0f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + max.y, fz + min.z, tex4.getInterpolatedU(1.0f), tex4.getInterpolatedV(0.8125f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);

    builder.quad();
    builder.vertex(fx + min.x, fy + min.y, fz + max.z, tex5.getInterpolatedU(0.8125f), tex5.getInterpolatedV(1.0f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + min.x, fy + min.y, fz + min.z, tex5.getInterpolatedU(0.8125f), tex5.getInterpolatedV(0.8125f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + min.z, tex5.getInterpolatedU(1.0f), tex5.getInterpolatedV(0.8125f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
    builder.vertex(fx + max.x, fy + min.y, fz + max.z, tex5.getInterpolatedU(1.0f), tex5.getInterpolatedV(1.0f), 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
}

void renderBlocks(RenderBuffer& rb, ChunkRenderCache& blocks) {
	rb.clear();

	const int32_t start_x = blocks.chunk_x << 4;
    const int32_t start_z = blocks.chunk_z << 4;

    for (int32_t x = start_x; x < start_x + 16; x++) {
        for (int32_t z = start_z; z < start_z + 16; z++) {
            for (int32_t y = 0; y < 256; y++) {
                const glm::ivec3 pos{x, y, z};

                auto block = blocks.getBlock(x, y, z);

				switch (block->getRenderType()) {
                case RenderType::Air:
                	break;
                case RenderType::Block:
                    renderBlock(pos, block, rb, blocks, true);
                    break;
                case RenderType::Leaves:
                	renderBlock(pos, block, rb, blocks, false);
                	break;
                case RenderType::Cross:
                	renderCross(pos, block, rb, blocks);
                	break;
                case RenderType::Liquid:
                	renderLiquid(pos, block, rb, blocks);
                    break;
                case RenderType::Pane:
                    renderPane(pos, block, rb, blocks);
					break;
                case RenderType::Torch:
                    renderTorch(pos, block, rb, blocks);
                    break;
                case RenderType::SnowLayer:
                    renderSnow(pos, block, rb, blocks);
                    break;
                case RenderType::Cactus:
                    renderCactus(pos, block, rb, blocks);
                    break;
                case RenderType::BambooStem:
                    renderBambooStem(pos, block, rb, blocks);
                    break;
				}
            }
        }
    }
}
#include "client/render/RenderBuffer.hpp"
#include "client/render/chunk/ChunkRenderCache.hpp"

#include "../../block/Block.hpp"
#include "../../block/BlockGraphics.hpp"
#include "../../block/material/Materials.hpp"
#include "../../TextureAtlas.hpp"

#include <glm/vec3.hpp>

struct ModelQuad {
    glm::vec3 p0;
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
};

struct ModelFace {
    glm::vec4 uv;
    TextureUVCoordinateSet texture;
};

struct ModelElement {
    glm::vec3 from;
    glm::vec3 to;
    std::vector<ModelFace> faces;

//    static auto make(const glm::vec3& from, const glm::vec3& to) -> ModelElement {
//        return ModelElement{
//            .from = from,
//            .to = to,
//            .faces = {
//                glm::vec4(from.x, from.z, to.x, to.z),
//                glm::vec4(from.x, from.z, to.x, to.z),
//                glm::vec4(from.x, from.y, to.x, to.y),
//                glm::vec4(from.x, from.y, to.x, to.y),
//                glm::vec4(from.x, from.y, to.x, to.y),
//                glm::vec4(from.x, from.y, to.x, to.y)
//            }
//        };
//    }
//    static auto make(float x0, float y0, float z0, float x1, float y1, float z1) -> ModelElement {
//        return make(glm::vec3(x0, y0, z0), glm::vec3(x1, y1, z1));
//    }
};

struct BlockModel {
    std::vector<ModelElement> elements;
};

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
	auto val = 0;//blocks.getData(ix, iy, iz).dv;

    float aoLights[4] {0.3, 0.6, 0.9, 1 };

	if (shouldRenderFace(blocks.getBlock(ix, iy, iz - 1), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy, iz - 1);
        const auto coords = graphics.southTexture->get(val);

        const auto c0 = blocks.getData(ix, iy + 1, iz - 1).isSolid();
        const auto c1 = blocks.getData(ix, iy - 1, iz - 1).isSolid();
        const auto c2 = blocks.getData(ix - 1, iy, iz - 1).isSolid();
        const auto c3 = blocks.getData(ix + 1, iy, iz - 1).isSolid();

        const int ao0 = vertexAO(c1, c2, blocks.getData(ix - 1, iy - 1, iz - 1).isSolid());
        const int ao1 = vertexAO(c0, c2, blocks.getData(ix - 1, iy + 1, iz - 1).isSolid());
        const int ao2 = vertexAO(c0, c3, blocks.getData(ix + 1, iy + 1, iz - 1).isSolid());
        const int ao3 = vertexAO(c1, c3, blocks.getData(ix + 1, iy - 1, iz - 1).isSolid());

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.7f);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.7f);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.7f);
	}

	if (shouldRenderFace(blocks.getBlock(ix + 1, iy, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix + 1, iy, iz);
        const auto coords = graphics.eastTexture->get(val);

        const auto c0 = blocks.getData(ix + 1, iy - 1, iz).isSolid();
        const auto c1 = blocks.getData(ix + 1, iy + 1, iz).isSolid();
        const auto c2 = blocks.getData(ix + 1, iy, iz + 1).isSolid();
        const auto c3 = blocks.getData(ix + 1, iy, iz - 1).isSolid();

        const int ao0 = vertexAO(c0, c3, blocks.getData(ix + 1, iy - 1, iz - 1).isSolid());
        const int ao1 = vertexAO(c1, c3, blocks.getData(ix + 1, iy + 1, iz - 1).isSolid());
        const int ao2 = vertexAO(c1, c2, blocks.getData(ix + 1, iy + 1, iz + 1).isSolid());
        const int ao3 = vertexAO(c0, c2, blocks.getData(ix + 1, iy - 1, iz + 1).isSolid());

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.8f);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.8f);
	}

	if (shouldRenderFace(blocks.getBlock(ix, iy, iz + 1), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy, iz + 1);
        const auto coords = graphics.northTexture->get(val);

        const auto c0 = blocks.getData(ix, iy - 1, iz + 1).isSolid();
        const auto c1 = blocks.getData(ix, iy + 1, iz + 1).isSolid();
        const auto c2 = blocks.getData(ix - 1, iy, iz + 1).isSolid();
        const auto c3 = blocks.getData(ix + 1, iy, iz + 1).isSolid();

        const int ao0 = vertexAO(c0, c3, blocks.getData(ix + 1, iy - 1, iz + 1).isSolid());
        const int ao1 = vertexAO(c1, c3, blocks.getData(ix + 1, iy + 1, iz + 1).isSolid());
        const int ao2 = vertexAO(c1, c2, blocks.getData(ix - 1, iy + 1, iz + 1).isSolid());
        const int ao3 = vertexAO(c0, c2, blocks.getData(ix - 1, iy - 1, iz + 1).isSolid());

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.8f);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.8f);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.8f);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.8f);
	}

	if (shouldRenderFace(blocks.getBlock(ix - 1, iy, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix - 1, iy, iz);
        const auto coords = graphics.westTexture->get(val);

        const auto c0 = blocks.getData(ix - 1, iy - 1, iz).isSolid();
        const auto c1 = blocks.getData(ix - 1, iy + 1, iz).isSolid();
        const auto c2 = blocks.getData(ix - 1, iy, iz - 1).isSolid();
        const auto c3 = blocks.getData(ix - 1, iy, iz + 1).isSolid();

        const int ao0 = vertexAO(c0, c3, blocks.getData(ix - 1, iy - 1, iz + 1).isSolid());
        const int ao1 = vertexAO(c1, c3, blocks.getData(ix - 1, iy + 1, iz + 1).isSolid());
        const int ao2 = vertexAO(c1, c2, blocks.getData(ix - 1, iy + 1, iz - 1).isSolid());
        const int ao3 = vertexAO(c0, c2, blocks.getData(ix - 1, iy - 1, iz - 1).isSolid());

        builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, packedLight, aoLights[ao0] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, aoLights[ao1] * 0.7f);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, packedLight, aoLights[ao2] * 0.7f);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, aoLights[ao3] * 0.7f);
	}

	if (shouldRenderFace(blocks.getBlock(ix, iy + 1, iz), block)) {
        const auto packedLight = blocks.getLightPacked(ix, iy + 1, iz);
		const auto coords = graphics.topTexture->get(val);

        const auto c0 = blocks.getData(ix, iy + 1, iz + 1).isSolid();
        const auto c1 = blocks.getData(ix, iy + 1, iz - 1).isSolid();
        const auto c2 = blocks.getData(ix - 1, iy + 1, iz).isSolid();
        const auto c3 = blocks.getData(ix + 1, iy + 1, iz).isSolid();

        const int ao0 = vertexAO(c1, c2, blocks.getData(ix - 1, iy + 1, iz - 1).isSolid());
        const int ao1 = vertexAO(c0, c2, blocks.getData(ix - 1, iy + 1, iz + 1).isSolid());
        const int ao2 = vertexAO(c0, c3, blocks.getData(ix + 1, iy + 1, iz + 1).isSolid());
        const int ao3 = vertexAO(c1, c3, blocks.getData(ix + 1, iy + 1, iz - 1).isSolid());

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
    auto val = 0;//blocks.getData(ix, iy, iz).dv;

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
    const auto [ix, iy, iz] = pos;
    const auto [fx, fy, fz] = glm::vec3(pos);

    auto& graphics = block->getGraphics();
	auto coords = graphics.southTexture->get(0);

	auto [r, g, b] = getTintColor(block->getTintType());

	auto builder = rb.getForLayer(block->getRenderLayer());

	constexpr float f = 0.146446609f;
	constexpr float s = 0.853553391f;

    const auto packedLight = blocks.getLightPacked(ix, iy, iz);

	builder.quad();
	builder.quadInv();
	builder.vertex(fx + f, fy + 0, fz + f, coords.minU, coords.minV, r, g, b, packedLight, 1.0f);
	builder.vertex(fx + f, fy + 1, fz + f, coords.minU, coords.maxV, r, g, b, packedLight, 1.0f);
	builder.vertex(fx + s, fy + 1, fz + s, coords.maxU, coords.maxV, r, g, b, packedLight, 1.0f);
	builder.vertex(fx + s, fy + 0, fz + s, coords.maxU, coords.minV, r, g, b, packedLight, 1.0f);

	builder.quad();
	builder.quadInv();
	builder.vertex(fx + f, fy + 0, fz + s, coords.minU, coords.minV, r, g, b, packedLight, 1.0f);
	builder.vertex(fx + f, fy + 1, fz + s, coords.minU, coords.maxV, r, g, b, packedLight, 1.0f);
	builder.vertex(fx + s, fy + 1, fz + f, coords.maxU, coords.maxV, r, g, b, packedLight, 1.0f);
	builder.vertex(fx + s, fy + 0, fz + f, coords.maxU, coords.minV, r, g, b, packedLight, 1.0f);
}

void renderLilyPad(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto [ix, iy, iz] = pos;
    const auto [fx, fy, fz] = glm::vec3(pos);

    auto& graphics = block->getGraphics();
    auto coords = graphics.southTexture->get(0);

    auto [r, g, b] = getTintColor(block->getTintType());

    auto builder = rb.getForLayer(block->getRenderLayer());

    const auto packedLight = blocks.getLightPacked(ix, iy, iz);

    builder.quad();
    builder.quadInv();
    builder.vertex(fx + 0, fy + 0.0625f, fz + 0, coords.minU, coords.minV, r, g, b, packedLight, 1.0f);
    builder.vertex(fx + 0, fy + 0.0625f, fz + 1, coords.minU, coords.maxV, r, g, b, packedLight, 1.0f);
    builder.vertex(fx + 1, fy + 0.0625f, fz + 1, coords.maxU, coords.maxV, r, g, b, packedLight, 1.0f);
    builder.vertex(fx + 1, fy + 0.0625f, fz + 0, coords.maxU, coords.minV, r, g, b, packedLight, 1.0f);
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

void renderModel(RenderLayerBuilder& builder, const glm::ivec3& pos, const BlockModel& model) {
    for (auto&& element : model.elements) {
        const auto from = element.from;
        const auto to = element.to;

        const auto p1 = glm::vec3(from.x, from.y, from.z);
        const auto p2 = glm::vec3(from.x, from.y, to.z);
        const auto p3 = glm::vec3(to.x, from.y, to.z);
        const auto p4 = glm::vec3(to.x, from.y, from.z);
        const auto p5 = glm::vec3(from.x, to.y, from.z);
        const auto p6 = glm::vec3(from.x, to.y, to.z);
        const auto p7 = glm::vec3(to.x, to.y, to.z);
        const auto p8 = glm::vec3(to.x, to.y, from.z);

        const auto quads = std::array{
            ModelQuad{p2, p1, p4, p3}, // down
            ModelQuad{p5, p6, p7, p8}, // up,
            ModelQuad{p3, p7, p6, p2}, // north
            ModelQuad{p1, p5, p8, p4}, // south
            ModelQuad{p2, p6, p5, p1}, // west
            ModelQuad{p4, p8, p7, p3}, // east
        };

        for (int i = 0; i < 6; i++) {
            const auto v0 = quads[i].p0 / 16.0f + glm::vec3(pos);
            const auto v1 = quads[i].p1 / 16.0f + glm::vec3(pos);
            const auto v2 = quads[i].p2 / 16.0f + glm::vec3(pos);
            const auto v3 = quads[i].p3 / 16.0f + glm::vec3(pos);

            auto&& tex = element.faces[i].texture;
            auto&& face = element.faces[i].uv / 16.0f;
            const auto uvs = std::array {
                tex.getInterpolatedU(face.x), tex.getInterpolatedV(face.y),
                tex.getInterpolatedU(face.x), tex.getInterpolatedV(face.w),
                tex.getInterpolatedU(face.z), tex.getInterpolatedV(face.w),
                tex.getInterpolatedU(face.z), tex.getInterpolatedV(face.y),
            };

            builder.quad();
            builder.vertex(v0.x, v0.y, v0.z, uvs[0], uvs[1], 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
            builder.vertex(v1.x, v1.y, v1.z, uvs[2], uvs[3], 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
            builder.vertex(v2.x, v2.y, v2.z, uvs[4], uvs[5], 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
            builder.vertex(v3.x, v3.y, v3.z, uvs[6], uvs[7], 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
        }
    }
}

void renderPane(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();

    const auto textures = std::array {
        graphics.bottomTexture->get(0),
        graphics.topTexture->get(0),
        graphics.northTexture->get(0),
        graphics.southTexture->get(0),
        graphics.westTexture->get(0),
        graphics.eastTexture->get(0)
    };

    auto model = BlockModel{};
    model.elements.emplace_back(ModelElement{
        .from = {7.2f, 0.0f, 7.2f},
        .to = {8.8f, 16.0f, 8.8f},
        .faces = {
            {.uv = glm::vec4(7.2f, 7.2f, 8.8f, 8.8f), .texture = textures[0]},
            {.uv = glm::vec4(7.2f, 7.2f, 8.8f, 8.8f), .texture = textures[1]},
            {.uv = glm::vec4(7.2f, 0.0f, 8.8f, 1.0f), .texture = textures[2]},
            {.uv = glm::vec4(7.2f, 0.0f, 8.8f, 1.0f), .texture = textures[3]},
            {.uv = glm::vec4(7.2f, 0.0f, 8.8f, 1.0f), .texture = textures[4]},
            {.uv = glm::vec4(7.2f, 0.0f, 8.8f, 1.0f), .texture = textures[5]}
        }
    });
    const auto val = blocks.getData(pos).dv;
    if (val & 1) {
        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(0, 0, 7.2),
            .to = glm::vec3(7.2, 16, 8.8),
            .faces = {
                {.uv = glm::vec4(  0, 7.2, 7.2, 8.8), .texture = textures[0]},
                {.uv = glm::vec4(  0, 7.2, 7.2, 8.8), .texture = textures[1]},
                {.uv = glm::vec4(  0,   0, 7.2,  16), .texture = textures[2]},
                {.uv = glm::vec4(  0,   0, 7.2,  16), .texture = textures[3]},
                {.uv = glm::vec4(7.2,   0, 8.8,  16), .texture = textures[4]},
                {.uv = glm::vec4(7.2,   0, 8.8,  16), .texture = textures[5]}
            }
        });
    }
    if (val & 2) {
        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(7.2, 0, 8.8),
            .to = glm::vec3(8.8, 16, 16),
            .faces = {
                {.uv = glm::vec4(7.2, 8.8, 8.8, 16), .texture = textures[0]},
                {.uv = glm::vec4(7.2, 8.8, 8.8, 16), .texture = textures[1]},
                {.uv = glm::vec4(7.2, 0, 8.8,   16), .texture = textures[2]},
                {.uv = glm::vec4(7.2, 0, 8.8,   16), .texture = textures[3]},
                {.uv = glm::vec4(8.8, 0, 16,    16), .texture = textures[4]},
                {.uv = glm::vec4(8.8, 0, 16,    16), .texture = textures[5]}
            }
        });
    }
    if (val & 4) {
        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(8.8, 0, 7.2),
            .to = glm::vec3(16, 16, 8.8),
            .faces = {
                {.uv = glm::vec4(8.8, 7.2, 16, 8.8), .texture = textures[0]},
                {.uv = glm::vec4(8.8, 7.2, 16, 8.8), .texture = textures[1]},
                {.uv = glm::vec4(8.8, 0, 16,    16), .texture = textures[2]},
                {.uv = glm::vec4(8.8, 0, 16,    16), .texture = textures[3]},
                {.uv = glm::vec4(7.2, 0, 8.8,   16), .texture = textures[4]},
                {.uv = glm::vec4(7.2, 0, 8.8,   16), .texture = textures[5]}
            }
        });
    }
    if (val & 8) {
        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(7.2, 0, 0),
            .to = glm::vec3(8.8, 16, 7.2),
            .faces = {
                {.uv = glm::vec4(7.2, 0, 8.8, 7.2), .texture = textures[0]},
                {.uv = glm::vec4(7.2, 0, 8.8, 7.2), .texture = textures[1]},
                {.uv = glm::vec4(7.2, 0, 8.8,  16), .texture = textures[2]},
                {.uv = glm::vec4(7.2, 0, 8.8,  16), .texture = textures[3]},
                {.uv = glm::vec4(0, 0, 7.2,    16), .texture = textures[4]},
                {.uv = glm::vec4(0, 0, 7.2,    16), .texture = textures[5]}
            }
        });
    }

    renderModel(builder, pos, model);
}

void renderFence(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();
    const auto textures = std::array {
        graphics.bottomTexture->get(0),
        graphics.topTexture->get(0),
        graphics.northTexture->get(0),
        graphics.southTexture->get(0),
        graphics.westTexture->get(0),
        graphics.eastTexture->get(0)
    };

    auto model = BlockModel{};

    model.elements.emplace_back(
        ModelElement{
            .from = glm::vec3(0.3f, 0.0f, 0.3f) * 16.0f,
            .to = glm::vec3(0.7f, 1.0f, 0.7f) * 16.0f,
            .faces = {
                {.uv = glm::vec4(0.3f, 0.3f, 0.7f, 0.7f) * 16.0f, .texture = textures[0]}, // down
                {.uv = glm::vec4(0.3f, 0.3f, 0.7f, 0.7f) * 16.0f, .texture = textures[1]}, // up
                {.uv = glm::vec4(0.3f, 0.0f, 0.7f, 1.0f) * 16.0f, .texture = textures[2]}, // north
                {.uv = glm::vec4(0.3f, 0.0f, 0.7f, 1.0f) * 16.0f, .texture = textures[3]}, // south
                {.uv = glm::vec4(0.3f, 0.0f, 0.7f, 1.0f) * 16.0f, .texture = textures[4]}, // west
                {.uv = glm::vec4(0.3f, 0.0f, 0.7f, 1.0f) * 16.0f, .texture = textures[5]}  // east
            }
        }
    );

    const auto val = blocks.getData(pos).dv;
    if (val & 1) {
        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(6.4, 4.8, 0),
            .to = glm::vec3(9.6, 8, 4.8),
            .faces = {
                {.uv = glm::vec4(6.4, 0, 9.6, 4.8), .texture = textures[0]},
                {.uv = glm::vec4(6.4, 0, 9.6, 4.8), .texture = textures[1]},
                {.uv = glm::vec4(6.4, 4.8, 9.6, 8), .texture = textures[2]},
                {.uv = glm::vec4(6.4, 4.8, 9.6, 8), .texture = textures[3]},
                {.uv = glm::vec4(0, 4.8, 4.8,   8), .texture = textures[4]},
                {.uv = glm::vec4(0, 4.8, 4.8,   8), .texture = textures[5]}
            }
        });

        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(6.4, 11.2, 0),
            .to = glm::vec3(9.6, 14.4, 4.8),
            .faces = {
                {.uv = glm::vec4(6.4, 0, 9.6,     4.8), .texture = textures[0]},
                {.uv = glm::vec4(6.4, 0, 9.6,     4.8), .texture = textures[1]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 14.4), .texture = textures[2]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 14.4), .texture = textures[3]},
                {.uv = glm::vec4(0, 11.2, 4.8,   14.4), .texture = textures[4]},
                {.uv = glm::vec4(0, 11.2, 4.8,   14.4), .texture = textures[5]}
            }
        });
    }
    if (val & 2) {
        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(11.2, 4.8, 6.4),
            .to = glm::vec3(16, 8, 9.6),
            .faces = {
                {.uv = glm::vec4(11.2, 6.4, 16, 9.6), .texture = textures[0]},
                {.uv = glm::vec4(11.2, 6.4, 16, 9.6), .texture = textures[1]},
                {.uv = glm::vec4(11.2, 4.8, 16,   8), .texture = textures[2]},
                {.uv = glm::vec4(11.2, 4.8, 16,   8), .texture = textures[3]},
                {.uv = glm::vec4(6.4, 4.8, 9.6,   8), .texture = textures[4]},
                {.uv = glm::vec4(6.4, 4.8, 9.6,   8), .texture = textures[5]}
            }
        });

        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(11.2, 11.2, 6.4),
            .to = glm::vec3(16, 14.4, 9.6),
            .faces = {
                {.uv = glm::vec4(11.2, 6.4, 16,   9.6), .texture = textures[0]},
                {.uv = glm::vec4(11.2, 6.4, 16,   9.6), .texture = textures[1]},
                {.uv = glm::vec4(11.2, 11.2, 16, 14.4), .texture = textures[2]},
                {.uv = glm::vec4(11.2, 11.2, 16, 14.4), .texture = textures[3]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 14.4), .texture = textures[4]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 14.4), .texture = textures[5]}
            }
        });
    }
    if (val & 4) {
        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(6.4, 4.8, 11.2),
            .to = glm::vec3(9.6, 8, 16),
            .faces = {
                {.uv = glm::vec4(6.4, 11.2, 9.6, 16), .texture = textures[0]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 16), .texture = textures[1]},
                {.uv = glm::vec4(6.4, 4.8, 9.6,   8), .texture = textures[2]},
                {.uv = glm::vec4(6.4, 4.8, 9.6,   8), .texture = textures[3]},
                {.uv = glm::vec4(11.2, 4.8, 16,   8), .texture = textures[4]},
                {.uv = glm::vec4(11.2, 4.8, 16,   8), .texture = textures[5]}
            }
        });

        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(6.4, 11.2, 11.2),
            .to = glm::vec3(9.6, 14.4, 16),
            .faces = {
                {.uv = glm::vec4(6.4, 11.2, 9.6,   16), .texture = textures[0]},
                {.uv = glm::vec4(6.4, 11.2, 9.6,   16), .texture = textures[1]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 14.4), .texture = textures[2]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 14.4), .texture = textures[3]},
                {.uv = glm::vec4(11.2, 11.2, 16, 14.4), .texture = textures[4]},
                {.uv = glm::vec4(11.2, 11.2, 16, 14.4), .texture = textures[5]}
            }
        });
    }
    if (val & 8) {
        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(0, 4.8, 6.4),
            .to = glm::vec3(4.8, 8, 9.6),
            .faces = {
                {.uv = glm::vec4(0, 6.4, 4.8, 9.6), .texture = textures[0]},
                {.uv = glm::vec4(0, 6.4, 4.8, 9.6), .texture = textures[1]},
                {.uv = glm::vec4(0, 4.8, 4.8,   8), .texture = textures[2]},
                {.uv = glm::vec4(0, 4.8, 4.8,   8), .texture = textures[3]},
                {.uv = glm::vec4(6.4, 4.8, 9.6, 8), .texture = textures[4]},
                {.uv = glm::vec4(6.4, 4.8, 9.6, 8), .texture = textures[5]}
            }
        });

        model.elements.emplace_back(ModelElement{
            .from = glm::vec3(0, 11.2, 6.4),
            .to = glm::vec3(4.8, 14.4, 9.6),
            .faces = {
                {.uv = glm::vec4(0, 6.4, 4.8,     9.6), .texture = textures[0]},
                {.uv = glm::vec4(0, 6.4, 4.8,     9.6), .texture = textures[1]},
                {.uv = glm::vec4(0, 11.2, 4.8,   14.4), .texture = textures[2]},
                {.uv = glm::vec4(0, 11.2, 4.8,   14.4), .texture = textures[3]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 14.4), .texture = textures[4]},
                {.uv = glm::vec4(6.4, 11.2, 9.6, 14.4), .texture = textures[5]}
            }
        });
    }
    renderModel(builder, pos, model);
}

void renderFenceGate(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();
    const auto textures = std::array {
        graphics.bottomTexture->get(0),
        graphics.topTexture->get(0),
        graphics.northTexture->get(0),
        graphics.southTexture->get(0),
        graphics.westTexture->get(0),
        graphics.eastTexture->get(0)
    };
    auto model = BlockModel{};

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(0, 4, 8),
        .to = glm::vec3(2, 15, 10),
        .faces = {
            {.uv = glm::vec4(0, 8,  2, 10), .texture = textures[0]},
            {.uv = glm::vec4(0, 8,  2, 10), .texture = textures[1]},
            {.uv = glm::vec4(0, 4,  2, 15), .texture = textures[2]},
            {.uv = glm::vec4(0, 4,  2, 15), .texture = textures[3]},
            {.uv = glm::vec4(8, 4, 10, 15), .texture = textures[4]},
            {.uv = glm::vec4(8, 4, 10, 15), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(0, 5, 14),
        .to = glm::vec3(2, 14, 16),
        .faces = {
            {.uv = glm::vec4( 0, 14,  2, 16), .texture = textures[0]},
            {.uv = glm::vec4( 0, 14,  2, 16), .texture = textures[1]},
            {.uv = glm::vec4( 0,  5,  2, 14), .texture = textures[2]},
            {.uv = glm::vec4( 0,  5,  2, 14), .texture = textures[3]},
            {.uv = glm::vec4(14,  5, 16, 14), .texture = textures[4]},
            {.uv = glm::vec4(14,  5, 16, 14), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(0, 5, 10),
        .to = glm::vec3(2, 8, 14),
        .faces = {
            {.uv = glm::vec4(0, 10, 2, 14), .texture = textures[0]},
            {.uv = glm::vec4(0, 10, 2, 14), .texture = textures[1]},
            {.uv = glm::vec4(0, 5, 2,   8), .texture = textures[2]},
            {.uv = glm::vec4(0, 5, 2,   8), .texture = textures[3]},
            {.uv = glm::vec4(10, 5, 14, 8), .texture = textures[4]},
            {.uv = glm::vec4(10, 5, 14, 8), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(0, 11, 10),
        .to = glm::vec3(2, 14, 14),
        .faces = {
            {.uv = glm::vec4(0, 10, 2,   14), .texture = textures[0]},
            {.uv = glm::vec4(0, 10, 2,   14), .texture = textures[1]},
            {.uv = glm::vec4(0, 11, 2,   14), .texture = textures[2]},
            {.uv = glm::vec4(0, 11, 2,   14), .texture = textures[3]},
            {.uv = glm::vec4(10, 11, 14, 14), .texture = textures[4]},
            {.uv = glm::vec4(10, 11, 14, 14), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(14, 4, 8),
        .to = glm::vec3(16, 15, 10),
        .faces = {
            {.uv = glm::vec4(14, 8, 16, 10), .texture = textures[0]},
            {.uv = glm::vec4(14, 8, 16, 10), .texture = textures[1]},
            {.uv = glm::vec4(14, 4, 16, 15), .texture = textures[2]},
            {.uv = glm::vec4(14, 4, 16, 15), .texture = textures[3]},
            {.uv = glm::vec4(8, 4, 10,  15), .texture = textures[4]},
            {.uv = glm::vec4(8, 4, 10,  15), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(14, 5, 14),
        .to = glm::vec3(16, 14, 16),
        .faces = {
            {.uv = glm::vec4(14, 14, 16, 16), .texture = textures[0]},
            {.uv = glm::vec4(14, 14, 16, 16), .texture = textures[1]},
            {.uv = glm::vec4(14, 5, 16,  14), .texture = textures[2]},
            {.uv = glm::vec4(14, 5, 16,  14), .texture = textures[3]},
            {.uv = glm::vec4(14, 5, 16,  14), .texture = textures[4]},
            {.uv = glm::vec4(14, 5, 16,  14), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(14, 5, 10),
        .to = glm::vec3(16, 8, 14),
        .faces = {
            {.uv = glm::vec4(14, 10, 16, 14), .texture = textures[0]},
            {.uv = glm::vec4(14, 10, 16, 14), .texture = textures[1]},
            {.uv = glm::vec4(14, 5, 16, 8), .texture = textures[1]},
            {.uv = glm::vec4(14, 5, 16, 8), .texture = textures[2]},
            {.uv = glm::vec4(10, 5, 14, 8), .texture = textures[3]},
            {.uv = glm::vec4(10, 5, 14, 8), .texture = textures[4]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(14, 11, 10),
        .to = glm::vec3(16, 14, 14),
        .faces = {
            {.uv = glm::vec4(14, 10, 16, 14), .texture = textures[0]},
            {.uv = glm::vec4(14, 10, 16, 14), .texture = textures[1]},
            {.uv = glm::vec4(14, 11, 16, 14), .texture = textures[2]},
            {.uv = glm::vec4(14, 11, 16, 14), .texture = textures[3]},
            {.uv = glm::vec4(10, 11, 14, 14), .texture = textures[4]},
            {.uv = glm::vec4(10, 11, 14, 14), .texture = textures[5]}
        }
    });
    renderModel(builder, pos, model);
}

void renderTrapdoor(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();

    auto model = BlockModel{};
//    create(0, 0, 0, 1, 0.1875f, 1);
    renderModel(builder, pos, model);
}

void renderCarpet(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();

    auto model = BlockModel{};
//    create(0, 0, 0, 1, 0.0625f, 1);
    renderModel(builder, pos, model);
}

void renderCoralFan(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();

    auto model = BlockModel{};
//    create(0, 0, 0, 1, 0.0625f, 1);
    renderModel(builder, pos, model);
}

void renderWallCoralFan(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();

    auto model = BlockModel{};
//    create(0, 0, 0, 1, 0.0625f, 1);
    renderModel(builder, pos, model);
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

    auto& graphics = block->getGraphics();
    const auto textures = std::array {
        graphics.bottomTexture->get(0),
        graphics.topTexture->get(0),
        graphics.northTexture->get(0),
        graphics.southTexture->get(0),
        graphics.westTexture->get(0),
        graphics.eastTexture->get(0)
    };

    auto model = BlockModel{};
    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(0, 0, 0),
        .to = glm::vec3(16, 2, 16),
        .faces = {
            {.uv = glm::vec4(0, 0, 16, 16), .texture = textures[0]},
            {.uv = glm::vec4(0, 0, 16, 16), .texture = textures[1]},
            {.uv = glm::vec4(0, 0, 16, 2), .texture = textures[2]},
            {.uv = glm::vec4(0, 0, 16, 2), .texture = textures[3]},
            {.uv = glm::vec4(0, 0, 16, 2), .texture = textures[4]},
            {.uv = glm::vec4(0, 0, 16, 2), .texture = textures[5]}
        }
    });
    renderModel(builder, pos, model);
}

void renderCactus(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    const auto [fx, fy, fz] = glm::vec3(pos);
    auto builder = rb.getForLayer(block->getRenderLayer());

    const auto min = glm::vec3{0.0f, 0.0f, 0.0f};
    const auto max = glm::vec3{1.0f, 1.0f, 1.0f};

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
    const auto textures = std::array {
        graphics.bottomTexture->get(0),
        graphics.topTexture->get(0),
        graphics.northTexture->get(0),
        graphics.southTexture->get(0),
        graphics.westTexture->get(0),
        graphics.eastTexture->get(0)
    };

    auto model = BlockModel{};
    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(6.5, 0, 6.5),
        .to = glm::vec3(9.5, 16, 9.5),
        .faces = {
            {.uv = glm::vec4(13, 9, 12, 12), .texture = textures[4]},
            {.uv = glm::vec4(13, 13, 16, 16), .texture = textures[4]},
            {.uv = glm::vec4(0, 16, 3, 0), .texture = textures[4]},
            {.uv = glm::vec4(0, 16, 3, 0), .texture = textures[4]},
            {.uv = glm::vec4(0, 16, 3, 0), .texture = textures[4]},
            {.uv = glm::vec4(0, 16, 3, 0), .texture = textures[4]}
        }
    });
    renderModel(builder, pos, model);
}

void renderButton(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();

    const auto textures = std::array {
        graphics.bottomTexture->get(0),
        graphics.topTexture->get(0),
        graphics.northTexture->get(0),
        graphics.southTexture->get(0),
        graphics.westTexture->get(0),
        graphics.eastTexture->get(0)
    };

    auto model = BlockModel{};
    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(5, 0, 6),
        .to = glm::vec3(11, 2, 10),
        .faces = {
            {.uv = glm::vec4(5, 6, 11, 10), .texture = textures[0]},
            {.uv = glm::vec4(5, 6, 11, 10), .texture = textures[1]},
            {.uv = glm::vec4(5, 0, 11, 2), .texture = textures[2]},
            {.uv = glm::vec4(5, 0, 11, 2), .texture = textures[3]},
            {.uv = glm::vec4(6, 0, 10, 2), .texture = textures[4]},
            {.uv = glm::vec4(6, 0, 10, 2), .texture = textures[5]}
        }
    });
    renderModel(builder, pos, model);
}

void renderAnvil(const glm::ivec3& pos, Block* block, RenderBuffer& rb, ChunkRenderCache& blocks) {
    auto builder = rb.getForLayer(block->getRenderLayer());
    auto& graphics = block->getGraphics();

    const auto textures = std::array {
        graphics.bottomTexture->get(0),
        graphics.topTexture->get(0),
        graphics.northTexture->get(0),
        graphics.southTexture->get(0),
        graphics.westTexture->get(0),
        graphics.eastTexture->get(0)
    };

    auto model = BlockModel{};
    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(0, 0, 4),
        .to = glm::vec3(16, 1, 12),
        .faces = {
            {.uv = glm::vec4(0, 4, 16, 12), .texture = textures[0]},
            {.uv = glm::vec4(0, 4, 16, 12), .texture = textures[1]},
            {.uv = glm::vec4(0, 0, 16, 1), .texture = textures[2]},
            {.uv = glm::vec4(0, 0, 16, 1), .texture = textures[3]},
            {.uv = glm::vec4(4, 0, 12, 1), .texture = textures[4]},
            {.uv = glm::vec4(4, 0, 12, 1), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(1, 0, 3),
        .to = glm::vec3(15, 1, 4),
        .faces = {
            {.uv = glm::vec4(1, 3, 15, 4), .texture = textures[0]},
            {.uv = glm::vec4(1, 3, 15, 4), .texture = textures[1]},
            {.uv = glm::vec4(1, 0, 15, 1), .texture = textures[2]},
            {.uv = glm::vec4(1, 0, 15, 1), .texture = textures[3]},
            {.uv = glm::vec4(3, 0, 4, 1), .texture = textures[4]},
            {.uv = glm::vec4(3, 0, 4, 1), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(1, 0, 12),
        .to = glm::vec3(15, 1, 13),
        .faces = {
            {.uv = glm::vec4(1, 12, 15, 13), .texture = textures[0]},
            {.uv = glm::vec4(1, 12, 15, 13), .texture = textures[1]},
            {.uv = glm::vec4(1, 0, 15, 1), .texture = textures[2]},
            {.uv = glm::vec4(1, 0, 15, 1), .texture = textures[3]},
            {.uv = glm::vec4(12, 0, 13, 1), .texture = textures[4]},
            {.uv = glm::vec4(12, 0, 13, 1), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(1, 1, 4),
        .to = glm::vec3(15, 4, 12),
        .faces = {
            {.uv = glm::vec4(1, 4, 15, 12), .texture = textures[0]},
            {.uv = glm::vec4(1, 4, 15, 12), .texture = textures[1]},
            {.uv = glm::vec4(1, 1, 15, 4), .texture = textures[2]},
            {.uv = glm::vec4(1, 1, 15, 4), .texture = textures[3]},
            {.uv = glm::vec4(4, 1, 12, 4), .texture = textures[4]},
            {.uv = glm::vec4(4, 1, 12, 4), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(4, 4, 5),
        .to = glm::vec3(12, 5, 12),
        .faces = {
            {.uv = glm::vec4(4, 5, 12, 12), .texture = textures[0]},
            {.uv = glm::vec4(4, 5, 12, 12), .texture = textures[1]},
            {.uv = glm::vec4(4, 4, 12, 5), .texture = textures[2]},
            {.uv = glm::vec4(4, 4, 12, 5), .texture = textures[3]},
            {.uv = glm::vec4(5, 4, 12, 5), .texture = textures[4]},
            {.uv = glm::vec4(5, 4, 12, 5), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(6, 5, 5),
        .to = glm::vec3(10, 10, 12),
        .faces = {
            {.uv = glm::vec4(6, 5, 10, 12), .texture = textures[0]},
            {.uv = glm::vec4(6, 5, 10, 12), .texture = textures[1]},
            {.uv = glm::vec4(6, 5, 10, 10), .texture = textures[2]},
            {.uv = glm::vec4(6, 5, 10, 10), .texture = textures[3]},
            {.uv = glm::vec4(5, 5, 12, 10), .texture = textures[4]},
            {.uv = glm::vec4(5, 5, 12, 10), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(2, 10, 4),
        .to = glm::vec3(14, 16, 12),
        .faces = {
            {.uv = glm::vec4(2, 4, 14, 12), .texture = textures[0]},
            {.uv = glm::vec4(2, 4, 14, 12), .texture = textures[1]},
            {.uv = glm::vec4(2, 10, 14, 16), .texture = textures[2]},
            {.uv = glm::vec4(2, 10, 14, 16), .texture = textures[3]},
            {.uv = glm::vec4(4, 10, 12, 16), .texture = textures[4]},
            {.uv = glm::vec4(4, 10, 12, 16), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(14, 11, 4),
        .to = glm::vec3(16, 15, 12),
        .faces = {
            {.uv = glm::vec4(14, 4, 16, 12), .texture = textures[0]},
            {.uv = glm::vec4(14, 4, 16, 12), .texture = textures[1]},
            {.uv = glm::vec4(14, 11, 16, 15), .texture = textures[2]},
            {.uv = glm::vec4(14, 11, 16, 15), .texture = textures[3]},
            {.uv = glm::vec4(4, 11, 12, 15), .texture = textures[4]},
            {.uv = glm::vec4(4, 11, 12, 15), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(0, 11, 4),
        .to = glm::vec3(2, 15, 12),
        .faces = {
            {.uv = glm::vec4(0, 4, 2, 12), .texture = textures[0]},
            {.uv = glm::vec4(0, 4, 2, 12), .texture = textures[1]},
            {.uv = glm::vec4(0, 11, 2, 15), .texture = textures[2]},
            {.uv = glm::vec4(0, 11, 2, 15), .texture = textures[3]},
            {.uv = glm::vec4(4, 11, 12, 15), .texture = textures[4]},
            {.uv = glm::vec4(4, 11, 12, 15), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(3, 11, 3),
        .to = glm::vec3(13, 15, 4),
        .faces = {
            {.uv = glm::vec4(3, 3, 13, 4), .texture = textures[0]},
            {.uv = glm::vec4(3, 3, 13, 4), .texture = textures[1]},
            {.uv = glm::vec4(3, 11, 13, 15), .texture = textures[2]},
            {.uv = glm::vec4(3, 11, 13, 15), .texture = textures[3]},
            {.uv = glm::vec4(3, 11, 4, 15), .texture = textures[4]},
            {.uv = glm::vec4(3, 11, 4, 15), .texture = textures[5]}
        }
    });

    model.elements.emplace_back(ModelElement{
        .from = glm::vec3(3, 11, 12),
        .to = glm::vec3(13, 15, 13),
        .faces = {
            {.uv = glm::vec4(3, 12, 13, 13), .texture = textures[0]},
            {.uv = glm::vec4(3, 12, 13, 13), .texture = textures[1]},
            {.uv = glm::vec4(3, 11, 13, 15), .texture = textures[2]},
            {.uv = glm::vec4(3, 11, 13, 15), .texture = textures[3]},
            {.uv = glm::vec4(12, 11, 13, 15), .texture = textures[4]},
            {.uv = glm::vec4(12, 11, 13, 15), .texture = textures[5]}
        }
    });
    renderModel(builder, pos, model);
}

void renderBlocks(RenderBuffer& rb, ChunkRenderCache& blocks) {
	rb.clear();

    const auto start_x = blocks.chunk_x << 4;
    const auto start_z = blocks.chunk_z << 4;

    for (int x = start_x; x < start_x + 16; x++) {
        for (int z = start_z; z < start_z + 16; z++) {
            for (int y = 0; y < 256; y++) {
                const auto pos = glm::ivec3{x, y, z};

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
                case RenderType::Fence:
                    renderFence(pos, block, rb, blocks);
					break;
                case RenderType::FenceGate:
                    renderFenceGate(pos, block, rb, blocks);
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
                case RenderType::LilyPad:
                    renderLilyPad(pos, block, rb, blocks);
                    break;
                case RenderType::Button:
                    renderButton(pos, block, rb, blocks);
                    break;
                case RenderType::Anvil:
                    renderAnvil(pos, block, rb, blocks);
                    break;
                case RenderType::Trapdoor:
                    renderTrapdoor(pos, block, rb, blocks);
                    break;
                case RenderType::Carpet:
                    renderCarpet(pos, block, rb, blocks);
                    break;
                case RenderType::CoralFan:
                    renderCoralFan(pos, block, rb, blocks);
                    break;
                case RenderType::WallCoralFan:
                    renderWallCoralFan(pos, block, rb, blocks);
                    break;
				}
            }
        }
    }

//    auto builder = rb.getForLayer(RenderLayer::Opaque);
//    const auto [fx, fy, fz] = glm::vec3(start_x, 0, start_z);
//
//    const auto min = glm::vec3(0, 0, 0);
//    const auto max = glm::vec3(16, 0, 16);
//
//    builder.quad();
//    builder.vertex(fx + min.x, fy + max.y, fz + min.z, 0, 0, 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
//    builder.vertex(fx + min.x, fy + max.y, fz + max.z, 0, 1, 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
//    builder.vertex(fx + max.x, fy + max.y, fz + max.z, 1, 1, 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
//    builder.vertex(fx + max.x, fy + max.y, fz + min.z, 1, 0, 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
}
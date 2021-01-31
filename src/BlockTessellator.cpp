#include "Block.hpp"
#include "Chunk.hpp"
#include "BlockReader.hpp"
#include "TextureAtlas.hpp"
#include "worldgenregion.hpp"

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

void renderBlock(int32 x, int32 y, int32 z, Block* block, RenderBuffer& rb, const WorldGenRegion& blocks) {
	const auto fx = float(x);// - 0.2f;
	const auto fy = float(y);// - 0.2f;
	const auto fz = float(z);// - 0.2f;

	auto [r, g, b] = getTintColor(block->tint);

	auto builder = rb.getForLayer(block->renderLayer);

	if (Block::id_to_block[(int) blocks.getBlock(x, y, z - 1).layer1.id]->renderType != block->renderType) {
		auto coords = block->graphics->southTexture->get(0);

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (Block::id_to_block[(int) blocks.getBlock(x + 1, y, z).layer1.id]->renderType != block->renderType) {
		auto coords = block->graphics->eastTexture->get(0);

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (Block::id_to_block[(int) blocks.getBlock(x, y, z + 1).layer1.id]->renderType != block->renderType) {
		auto coords = block->graphics->northTexture->get(0);

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (Block::id_to_block[(int) blocks.getBlock(x - 1, y, z).layer1.id]->renderType != block->renderType) {
		auto coords = block->graphics->westTexture->get(0);

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 255 || Block::id_to_block[(int) blocks.getBlock(x, y + 1, z).layer1.id]->renderType != block->renderType) {
		auto coords = block->graphics->topTexture->get(0);

		builder.quad();
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

    if (block->tint == Tint::Grass) {
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
    }

	if (y == 0 || Block::id_to_block[(int) blocks.getBlock(x, y - 1, z).layer1.id]->renderType != block->renderType) {
		auto coords = block->graphics->bottomTexture->get(0);

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}
}

void renderCross(int32 x, int32 y, int32 z, Block* block, RenderBuffer& rb, const WorldGenRegion& blocks) {
	const auto fx = float(x);// - 0.2f;
	const auto fy = float(y);// - 0.2f;
	const auto fz = float(z);// - 0.2f;

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

void renderLiquid(int32 x, int32 y, int32 z, Block* block, RenderBuffer& rb, const WorldGenRegion& blocks) {
	const auto fx = float(x);// - 0.2f;
	const auto fy = float(y);// - 0.2f;
	const auto fz = float(z);// - 0.2f;

	uint8 r = 0x44;
	uint8 g = 0xAF;
	uint8 b = 0xF5;

	auto builder = rb.getForLayer(block->renderLayer);

	bool up_is_liquid = Block::id_to_block[(int) blocks.getBlock(x, y + 1, z).layer1.id]->renderType == RenderType::Liquid;

	if (Block::id_to_block[(int) blocks.getBlock(x, y, z - 1).layer1.id]->renderType == RenderType::Air) {
		auto coords = block->graphics->southTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (Block::id_to_block[(int) blocks.getBlock(x + 1, y, z).layer1.id]->renderType == RenderType::Air) {
		auto coords = block->graphics->eastTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (Block::id_to_block[(int) blocks.getBlock(x, y, z + 1).layer1.id]->renderType == RenderType::Air) {
		auto coords = block->graphics->northTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (Block::id_to_block[(int) blocks.getBlock(x - 1, y, z).layer1.id]->renderType == RenderType::Air) {
		auto coords = block->graphics->westTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 255 || Block::id_to_block[(int) blocks.getBlock(x, y + 1, z).layer1.id]->renderType == RenderType::Air) {
		auto coords = block->graphics->topTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;


		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 0 || Block::id_to_block[(int) blocks.getBlock(x, y - 1, z).layer1.id]->renderType == RenderType::Air) {
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

void renderBox(RenderLayerBuilder& builder, int32 x, int32 y, int32 z, Block* block, glm::vec3 min, glm::vec3 max) {
    const auto fx = float(x);// - 0.2f;
    const auto fy = float(y);// - 0.2f;
    const auto fz = float(z);// - 0.2f;

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

void renderPane(int32 x, int32 y, int32 z, Block* block, RenderBuffer& rb, const WorldGenRegion& blocks) {
    auto builder = rb.getForLayer(block->renderLayer);

    auto val = blocks.getBlock(x, y, z).layer1.val;

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

void renderBlocks(RenderBuffer& rb, BlockTable& global_pallete, const WorldGenRegion& blocks) {
	rb.clear();

	int32 start_x = blocks.chunk_x << 4;
	int32 start_z = blocks.chunk_z << 4;

    for (int32 x = start_x; x < start_x + 16; x++) {
        for (int32 z = start_z; z < start_z + 16; z++) {
            for (int32 y = 0; y < 256; y++) {
                BlockLayers layers = blocks.getBlock(x, y, z);

                auto block = Block::id_to_block[(int) layers.layer1.id];

				switch (block->renderType) {
                case RenderType::Air:
                	break;
                case RenderType::Block:
                case RenderType::Leaves:
                	renderBlock(x, y, z, block, rb, blocks);
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

//                block = Block::id_to_block[(int) layers.layer1.id];
//                switch (block->renderType) {
//                case RenderType::Air:
//                    break;
//                case RenderType::Block:
//                case RenderType::Leaves:
//                    renderBlock(x, y, z, block, rb, blocks);
//                    break;
//                case RenderType::Cross:
//                    renderCross(x, y, z, block, rb, blocks);
//                    break;
//                case RenderType::Liquid:
//                    renderLiquid(x, y, z, block, rb, blocks);
//                    break;
//                }
            }
        }
    }
}
#include "block.hpp"
#include "chunk.hpp"
#include "block_reader.hpp"
#include "texture_atlas.hpp"

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

void renderBlock(int32 x, int32 y, int32 z, BlockState blockState, RenderBuffer& rb, IBlockReader auto const& blocks) {
	const auto fx = float(x);// - 0.5f;
	const auto fy = float(y);// - 0.5f;
	const auto fz = float(z);// - 0.5f;

	auto [r, g, b] = getTintColor(blockState.block->tint);

	auto builder = rb.getForLayer(blockState.block->renderLayer);

	if (blocks.getBlock(x, y, z - 1).block->renderType != blockState.block->renderType) {
		auto coords = blockState.block->graphics->southTexture->get(0);

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x + 1, y, z).block->renderType != blockState.block->renderType) {
		auto coords = blockState.block->graphics->eastTexture->get(0);

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x, y, z + 1).block->renderType != blockState.block->renderType) {
		auto coords = blockState.block->graphics->northTexture->get(0);

		builder.quad();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x - 1, y, z).block->renderType != blockState.block->renderType) {
		auto coords = blockState.block->graphics->westTexture->get(0);

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 255 || blocks.getBlock(x, y + 1, z).block->renderType != blockState.block->renderType) {
		auto coords = blockState.block->graphics->topTexture->get(0);

		builder.quad();
		builder.vertex(fx + 0, fy + 1, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 1, fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 1, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 0 || blocks.getBlock(x, y - 1, z).block->renderType != blockState.block->renderType) {
		auto coords = blockState.block->graphics->bottomTexture->get(0);

		builder.quad();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}
}

void renderCross(int32 x, int32 y, int32 z, BlockState blockState, RenderBuffer& rb, IBlockReader auto const& blocks) {
	const auto fx = float(x);// - 0.5f;
	const auto fy = float(y);// - 0.5f;
	const auto fz = float(z);// - 0.5f;

	auto coords = blockState.block->graphics->southTexture->get(0);

	auto [r, g, b] = getTintColor(blockState.block->tint);

	auto builder = rb.getForLayer(blockState.block->renderLayer);

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

void renderLiquid(int32 x, int32 y, int32 z, BlockState blockState, RenderBuffer& rb, IBlockReader auto const& blocks) {
	const auto fx = float(x);// - 0.5f;
	const auto fy = float(y);// - 0.5f;
	const auto fz = float(z);// - 0.5f;

	uint8 r = 0x44;
	uint8 g = 0xAF;
	uint8 b = 0xF5;

	auto builder = rb.getForLayer(blockState.block->renderLayer);

	bool up_is_liquid = blocks.getBlock(x, y + 1, z).block->renderType == RenderType::Liquid;

	if (blocks.getBlock(x, y, z - 1).block->renderType == RenderType::Air) {
		auto coords = blockState.block->graphics->southTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x + 1, y, z).block->renderType == RenderType::Air) {
		auto coords = blockState.block->graphics->eastTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x, y, z + 1).block->renderType == RenderType::Air) {
		auto coords = blockState.block->graphics->northTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (blocks.getBlock(x - 1, y, z).block->renderType == RenderType::Air) {
		auto coords = blockState.block->graphics->westTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 255 || blocks.getBlock(x, y + 1, z).block->renderType == RenderType::Air) {
		auto coords = blockState.block->graphics->topTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;


		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 1, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + (up_is_liquid ? 1 : 0.9375f), fz + 0, coords.maxU, coords.minV, r, g, b, 0xFF);
	}

	if (y == 0 || blocks.getBlock(x, y - 1, z).block->renderType == RenderType::Air) {
		auto coords = blockState.block->graphics->bottomTexture->get(0);
		coords.maxV = coords.minV + (coords.maxV - coords.minV) / 32.0f;

		builder.quad();
		builder.quadInv();
		builder.vertex(fx + 0, fy + 0, fz + 1, coords.minU, coords.minV, r, g, b, 0xFF);
		builder.vertex(fx + 0, fy + 0, fz + 0, coords.minU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 0, coords.maxU, coords.maxV, r, g, b, 0xFF);
		builder.vertex(fx + 1, fy + 0, fz + 1, coords.maxU, coords.minV, r, g, b, 0xFF);
	}
}

void renderBlocks(RenderBuffer& rb, IBlockReader auto const& blocks) {
	rb.clear();

	int32 start_x = blocks.chunk_x << 4;
	int32 start_z = blocks.chunk_z << 4;

    for (int32 x = start_x; x < start_x + 16; x++) {
        for (int32 z = start_z; z < start_z + 16; z++) {
            for (int32 y = 0; y < 256; y++) {
                auto blockState = blocks.getBlock(x, y, z);

                if (blockState.block->renderType == RenderType::Air) {
                    continue;
                }

				switch (blockState.block->renderType) {
                case RenderType::Air:
                	break;
                case RenderType::Block:
                case RenderType::Leaves:
                	renderBlock(x, y, z, blockState, rb, blocks);
                	break;
                case RenderType::Cross:
                	renderCross(x, y, z, blockState, rb, blocks);
                	break;
                case RenderType::Liquid:
                	renderLiquid(x, y, z, blockState, rb, blocks);
					break;
				}
            }
        }
    }
}

#include "worldgenregion.hpp"

template void renderBlocks(RenderBuffer& rb, WorldGenRegion<1ul> const& blocks);
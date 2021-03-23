#pragma once

#include <glm/vec4.hpp>

#include <map>
#include <vector>
#include <string>

struct BlockTable;
struct BlockGraphics;

enum class Tint {
	None,
	Grass,
	Foliage
};

enum class RenderType {
	Air,
	Liquid,
	Block,
	Leaves,
	Cross,
	Pane,
	Torch
};

enum class RenderLayer {
	Opaque,
	Cutout,
	Transparent
};

struct Block {
	explicit Block(int id);

	auto setRenderType(RenderType renderTypeIn) -> Block* {
		renderType = renderTypeIn;
		return this;
	}

	auto setRenderLayer(RenderLayer renderLayerIn) -> Block* {
		renderLayer = renderLayerIn;
		return this;
	}

	auto setTint(Tint tintIn) -> Block* {
		tint = tintIn;
		return this;
	}

    uint16_t id;
	Tint tint = Tint::None;
	RenderType renderType = RenderType::Block;
	RenderLayer renderLayer = RenderLayer::Opaque;
    BlockGraphics* graphics{nullptr};
};
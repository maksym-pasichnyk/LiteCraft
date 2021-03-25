#pragma once

#include "BlockData.hpp"
#include "material/Material.hpp"
#include "material/Materials.hpp"

#include <glm/vec4.hpp>

#include <map>
#include <vector>
#include <string>

struct Material;
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

using LightLevelFn = int32_t(*)(BlockData);

struct Block {
    explicit Block(int id);
    explicit Block(int id, Material* material);

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
	auto setLightLevel(LightLevelFn lightLevelIn) -> Block* {
        lightLevel = lightLevelIn;
	    return this;
	}

    auto getDefaultState() const -> BlockData {
	    return BlockData{static_cast<uint16_t>(id), 0};
	}

    auto getStateWithMeta(int32_t meta) const -> BlockData {
        return BlockData{static_cast<uint16_t>(id), static_cast<uint16_t>(meta)};
    }

    auto getMaterial() const -> Material* {
	    return material ?: Materials::ROCK;
	}

	auto getLightLevel(BlockData data) const -> int32_t {
	    return lightLevel(data);
	}

    int32_t id = -1;
    Material* material = nullptr;
    LightLevelFn lightLevel = [] (BlockData data) -> int32_t {
        return 0;
    };
	Tint tint = Tint::None;
	RenderType renderType = RenderType::Block;
	RenderLayer renderLayer = RenderLayer::Opaque;
    BlockGraphics* graphics{nullptr};
};
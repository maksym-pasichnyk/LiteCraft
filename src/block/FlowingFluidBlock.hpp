#pragma once

#include "Block.hpp"

enum class Fluids {
    WATER,
    LAVA
};

struct FlowingFluidBlock : Block {
    FlowingFluidBlock(int id, Fluids fluid, Properties properties) : Block(id, std::move(properties)) {}

    RenderType getRenderType() const override {
        return RenderType::Liquid;
    }
};
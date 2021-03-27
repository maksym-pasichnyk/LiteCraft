#pragma once

#include "Block.hpp"

struct AirBlock : Block {
    explicit AirBlock(int id, Properties properties) : Block(id, std::move(properties)) {

    }

    RenderType getRenderType() const override {
        return RenderType::Air;
    }
};
#pragma once

#include "../particles/ParticleType.hpp"
#include "Block.hpp"

struct TorchBlock : Block {
    TorchBlock(int id, Properties properties, ParticleType particleType) : Block(id, std::move(properties)) {}

    RenderType getRenderType() const override {
        return RenderType::Torch;
    }
};
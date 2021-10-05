#pragma once

#include "../particles/ParticleType.hpp"
#include "Block.hpp"

struct TorchBlock : Block {
    TorchBlock(int id, BlockBehaviour behaviour, ParticleType particleType) : Block(id, std::move(behaviour)) {}

//    RenderType getRenderType() const override {
//        return RenderType::Torch;
//    }
};
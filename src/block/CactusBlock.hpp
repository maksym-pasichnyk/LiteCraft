#pragma once

#include "Block.hpp"

struct CactusBlock : Block {
    struct Payload {
        uint16_t age : 8;
        uint16_t : 8;
    };

    static constexpr auto AGE = BlockStateProperty::AGE_0_15;

    using Block::Block;

    bool isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;

    RenderType getRenderType() const override {
        return RenderType::Cactus;
    }

    RenderLayer getRenderLayer() const override {
        return RenderLayer::Cutout;
    }

    void fillStateContainer() override {
        bind<AGE, get_AGE, set_AGE>();
    }

    static auto get_AGE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.age;
    }

    static auto set_AGE(BlockData state, int age) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.age = age;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
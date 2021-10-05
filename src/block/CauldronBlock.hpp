#pragma once

#include "Block.hpp"

struct CauldronBlock : Block {
    struct Payload {
        uint16_t level : 2;
        uint16_t : 14;
    };
    
    static constexpr auto LEVEL = Property::LEVEL_0_3;

    using Block::Block;

    void fillStateContainer() override {
        bind<LEVEL, get_LEVEL, set_LEVEL>();
    }

    static auto get_LEVEL(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.level;
    }

    static auto set_LEVEL(BlockData state, int level) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.level = static_cast<uint16_t>(level);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
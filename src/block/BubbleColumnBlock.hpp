#pragma once

#include "Block.hpp"

struct BubbleColumnBlock : Block {
    struct Payload {
        uint16_t drag : 1;
        uint16_t : 15;
    };

    static constexpr auto DRAG = BlockStateProperty::DRAG;
    
    using Block::Block;

    void fillStateContainer() override {
        bind<DRAG, get_DRAG, set_DRAG>();
    }

    static auto get_DRAG(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.drag == 1;
    }

    static auto set_DRAG(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.drag = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
#pragma once

#include "Block.hpp"

struct TNTBlock : Block {
    struct Payload {
        uint16_t unstable : 1;
        uint16_t : 15;
    };

    static constexpr auto UNSTABLE = BlockStateProperty::UNSTABLE;

    using Block::Block;
    
    void fillStateContainer() override {
        bind<UNSTABLE, get_UNSTABLE, set_UNSTABLE>();
    }
    
    static auto set_UNSTABLE(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.unstable = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_UNSTABLE(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.unstable == 1;
    }
};
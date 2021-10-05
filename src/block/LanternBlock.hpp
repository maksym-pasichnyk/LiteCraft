#pragma once

#include "Block.hpp"

struct LanternBlock : Block {
    using Block::Block;

    struct Payload {
        uint16_t hanging : 1;
        uint16_t : 15;
    };

    static constexpr auto HANGING = Property::HANGING;

    void fillStateContainer() override {
        bind<HANGING, get_HANGING, set_HANGING>();
    }

    static auto get_HANGING(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.hanging == 1;
    }

    static auto set_HANGING(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.hanging = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
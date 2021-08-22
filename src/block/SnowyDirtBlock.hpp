#pragma once

#include "Block.hpp"
#include "../state/BlockStateProperties.hpp"

struct SnowyDirtBlock : Block {
    struct Payload {
        uint16_t snowy : 1;
        uint16_t : 15;
    };

    static constexpr auto SNOWY = BlockStateProperty::SNOWY;

    using Block::Block;

    void fillStateContainer() override {
        bind<SNOWY, get_SNOWY, set_SNOWY>();
    }

    static auto get_SNOWY(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.snowy == 1;
    }

    static auto set_SNOWY(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.snowy = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

};
#pragma once

#include "Block.hpp"

struct RespawnAnchorBlock : Block {
    using Block::Block;
    
    struct Payload {
        uint16_t charges : 4;
        uint16_t : 12;
    };

    static constexpr auto CHARGES = Property::CHARGES;

    void fillStateContainer() override {
        bind<CHARGES, get_CHARGES, set_CHARGES>();
    }

    static auto get_CHARGES(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.charges;
    }

    static auto set_CHARGES(BlockData state, int charges) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.charges = charges;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
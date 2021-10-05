#pragma once

#include "Block.hpp"

struct CakeBlock : Block {
    struct Payload {
        uint16_t bites : 3;
        uint16_t : 13;
    };

    static constexpr auto BITES = Property::BITES_0_6;

    using Block::Block;

    void fillStateContainer() override {
        bind<BITES, get_BITES, set_BITES>();
    }

    static auto get_BITES(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.bites;
    }

    static auto set_BITES(BlockData state, int bites) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.bites = bites;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
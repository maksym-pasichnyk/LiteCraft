#pragma once

#include "BushBlock.hpp"

struct SeaPickleBlock : BushBlock {
    struct Payload {
        uint16_t pickles : 2;
        uint16_t : 14;
    };

    static constexpr auto PICKLES = Property::PICKLES_1_4;

    using BushBlock::BushBlock;

    void fillStateContainer() override {
        bind<PICKLES, get_PICKLES, set_PICKLES>();
    }

    static auto get_PICKLES(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.pickles + 1;
    }

    static auto set_PICKLES(BlockData state, int pickles) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.pickles = static_cast<uint16_t>(pickles - 1);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
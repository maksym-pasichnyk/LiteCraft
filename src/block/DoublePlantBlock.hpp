#pragma once

#include "BushBlock.hpp"

struct DoublePlantBlock : BushBlock {
    struct Payload {
        uint16_t half : 1;
        uint16_t : 15;
    };

    static constexpr auto HALF = Property::DOUBLE_BLOCK_HALF;

    using BushBlock::BushBlock;

    void fillStateContainer() override {
        bind<HALF, get_HALF, set_HALF>();
    }

    static auto get_HALF(BlockData state) -> DoubleBlockHalf {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<DoubleBlockHalf>(payload.half);
    }

    static auto set_HALF(BlockData state, DoubleBlockHalf half) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.half = static_cast<uint16_t>(half);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
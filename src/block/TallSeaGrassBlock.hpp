#pragma once

#include "DoublePlantBlock.hpp"

struct TallSeaGrassBlock : DoublePlantBlock {
    struct Payload {
        uint16_t half : 2;
        uint16_t : 14;
    };

    static constexpr auto HALF = Property::DOUBLE_BLOCK_HALF;

    using DoublePlantBlock::DoublePlantBlock;

    void fillStateContainer() override {
        bind<HALF, get_HALF, set_HALF>();
    }

    static auto set_HALF(BlockData state, DoubleBlockHalf half) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.half = static_cast<uint16_t>(half);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_HALF(BlockData state) -> DoubleBlockHalf {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<DoubleBlockHalf>(payload.half);
    }
};
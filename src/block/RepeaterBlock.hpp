#pragma once

#include "Block.hpp"

struct RepeaterBlock : Block {
    static constexpr auto FACING = Property::HORIZONTAL_FACING;
    static constexpr auto DELAY = Property::DELAY_1_4;

    using Block::Block;

    struct Payload {
        uint16_t facing : 3;
        uint16_t delay : 2;
        uint16_t : 11;
    };

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<DELAY, get_DELAY, set_DELAY>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_DELAY(BlockData state, int delay) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.delay = delay - 1;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_DELAY(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.delay + 1;
    }
};
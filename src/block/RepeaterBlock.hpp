#pragma once

#include "Block.hpp"

struct RepeaterBlock : Block {
    static constexpr auto FACING = Property::HORIZONTAL_FACING;
    static constexpr auto DELAY = Property::DELAY_1_4;
    static constexpr auto LOCKED = Property::LOCKED;
    static constexpr auto POWERED = Property::POWERED;

    using Block::Block;

    struct Payload {
        uint16_t facing : 3;
        uint16_t delay : 2;
        uint16_t locked : 1;
        uint16_t powered : 1;
        uint16_t : 9;
    };

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<DELAY, get_DELAY, set_DELAY>();
        bind<LOCKED, get_LOCKED, set_LOCKED>();
        bind<POWERED, get_POWERED, set_POWERED>();
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

    static auto set_LOCKED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.locked = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
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

    static auto get_LOCKED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.locked == 1;
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }
};
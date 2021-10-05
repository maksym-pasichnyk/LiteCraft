#pragma once

#include "HorizontalBlock.hpp"

struct FenceGateBlock : HorizontalBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t powered : 1;
        uint16_t wall : 1;
        uint16_t open : 1;
        uint16_t : 10;
    };

    static constexpr auto OPEN = Property::OPEN;
    static constexpr auto WALL = Property::IN_WALL;
    static constexpr auto POWERED = Property::POWERED;

    using HorizontalBlock::HorizontalBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<OPEN, get_OPEN, set_OPEN>();
        bind<WALL, get_WALL, set_WALL>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_OPEN(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.open = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_WALL(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.wall = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }

    static auto get_OPEN(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.open == 1;
    }

    static auto get_WALL(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.wall == 1;
    }
};
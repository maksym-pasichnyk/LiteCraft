#pragma once

#include "FourWayBlock.hpp"

struct FenceBlock : FourWayBlock {
    struct Payload {
        uint16_t north : 1;
        uint16_t south : 1;
        uint16_t east : 1;
        uint16_t west : 1;
        uint16_t : 12;
    };

    using FourWayBlock::FourWayBlock;

    void fillStateContainer() override {
        bind<EAST, get_EAST, set_EAST>();
        bind<NORTH, get_NORTH, set_NORTH>();
        bind<SOUTH, get_SOUTH, set_SOUTH>();
        bind<WEST, get_WEST, set_WEST>();
    }

    static auto get_EAST(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.east == 1;
    }

    static auto get_NORTH(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.north == 1;
    }

    static auto get_SOUTH(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.south == 1;
    }

    static auto get_WEST(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.west == 1;
    }

    static auto set_EAST(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.east = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_NORTH(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.north = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_SOUTH(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.south = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_WEST(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.west = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
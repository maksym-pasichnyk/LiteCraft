#pragma once

#include "AbstractFireBlock.hpp"

struct FireBlock : AbstractFireBlock {
    using AbstractFireBlock::AbstractFireBlock;

    struct Payload {
        uint16_t age : 4;
        uint16_t north : 1;
        uint16_t south : 1;
        uint16_t east : 1;
        uint16_t west : 1;
        uint16_t up : 1;
        uint16_t : 7;
    };

    static constexpr auto AGE = Property::AGE_0_15;
    static constexpr auto NORTH = Property::NORTH;
    static constexpr auto SOUTH = Property::SOUTH;
    static constexpr auto EAST = Property::EAST;
    static constexpr auto WEST = Property::WEST;
    static constexpr auto UP = Property::UP;

    void fillStateContainer() override {
        bind<AGE, get_AGE, set_AGE>();
        bind<NORTH, get_NORTH, set_NORTH>();
        bind<SOUTH, get_SOUTH, set_SOUTH>();
        bind<EAST, get_EAST, set_EAST>();
        bind<WEST, get_WEST, set_WEST>();
        bind<UP, get_UP, set_UP>();
    }

    static auto get_AGE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.age;
    }

    static auto set_AGE(BlockData state, int age) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.age = age;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_NORTH(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.north == 1;
    }

    static auto get_SOUTH(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.south == 1;
    }

    static auto get_EAST(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.east == 1;
    }

    static auto get_WEST(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.west == 1;
    }

    static auto get_UP(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.up == 1;
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

    static auto set_EAST(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.east = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_WEST(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.west = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_UP(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.up = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
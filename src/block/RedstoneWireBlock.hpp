#pragma once

#include "Block.hpp"

struct RedstoneWireBlock : Block {
    struct Payload {
        uint16_t power : 4;
        uint16_t north : 2;
        uint16_t south : 2;
        uint16_t east : 2;
        uint16_t west : 2;
        uint16_t : 4;
    };
    
    static constexpr auto POWER = BlockStateProperty::POWER_0_15;
    static constexpr auto NORTH = BlockStateProperty::REDSTONE_NORTH;
    static constexpr auto EAST = BlockStateProperty::REDSTONE_EAST;
    static constexpr auto SOUTH = BlockStateProperty::REDSTONE_SOUTH;
    static constexpr auto WEST = BlockStateProperty::REDSTONE_WEST;

    using Block::Block;

    void fillStateContainer() override {
        bind<POWER, get_POWER, set_POWER>();
        bind<EAST, get_EAST, set_EAST>();
        bind<NORTH, get_NORTH, set_NORTH>();
        bind<SOUTH, get_SOUTH, set_SOUTH>();
        bind<WEST, get_WEST, set_WEST>();
    }

    static auto get_POWER(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.power;
    }

    static auto get_EAST(BlockData state) -> RedstoneSide {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<RedstoneSide>(payload.east);
    }

    static auto get_NORTH(BlockData state) -> RedstoneSide {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<RedstoneSide>(payload.north);
    }

    static auto get_SOUTH(BlockData state) -> RedstoneSide {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<RedstoneSide>(payload.south);
    }

    static auto get_WEST(BlockData state) -> RedstoneSide {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<RedstoneSide>(payload.west);
    }

    static auto set_POWER(BlockData state, int power) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.power = power;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_EAST(BlockData state, RedstoneSide height) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.east = static_cast<uint16_t>(height);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_NORTH(BlockData state, RedstoneSide height) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.north = static_cast<uint16_t>(height);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_SOUTH(BlockData state, RedstoneSide height) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.south = static_cast<uint16_t>(height);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_WEST(BlockData state, RedstoneSide height) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.west = static_cast<uint16_t>(height);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
#pragma once

#include "Block.hpp"

struct WallBlock : Block {
    struct Payload {
        uint16_t up : 1;
        uint16_t north : 2;
        uint16_t south : 2;
        uint16_t east : 2;
        uint16_t west : 2;
        uint16_t : 7;
    };

    static constexpr auto UP = BlockStateProperty::UP;
    static constexpr auto EAST = BlockStateProperty::WALL_HEIGHT_EAST;
    static constexpr auto NORTH = BlockStateProperty::WALL_HEIGHT_NORTH;
    static constexpr auto SOUTH = BlockStateProperty::WALL_HEIGHT_SOUTH;
    static constexpr auto WEST = BlockStateProperty::WALL_HEIGHT_WEST;

    using Block::Block;

    void fillStateContainer() override {
        bind<UP, get_UP, set_UP>();
        bind<EAST, get_EAST, set_EAST>();
        bind<NORTH, get_NORTH, set_NORTH>();
        bind<SOUTH, get_SOUTH, set_SOUTH>();
        bind<WEST, get_WEST, set_WEST>();
    }

    static auto get_UP(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.up == 1;
    }

    static auto get_EAST(BlockData state) -> WallHeight {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<WallHeight>(payload.east);
    }

    static auto get_NORTH(BlockData state) -> WallHeight {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<WallHeight>(payload.north);
    }

    static auto get_SOUTH(BlockData state) -> WallHeight {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<WallHeight>(payload.south);
    }

    static auto get_WEST(BlockData state) -> WallHeight {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<WallHeight>(payload.west);
    }

    static auto set_UP(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.up = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_EAST(BlockData state, WallHeight height) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.east = static_cast<uint16_t>(height);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_NORTH(BlockData state, WallHeight height) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.north = static_cast<uint16_t>(height);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_SOUTH(BlockData state, WallHeight height) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.south = static_cast<uint16_t>(height);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_WEST(BlockData state, WallHeight height) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.west = static_cast<uint16_t>(height);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

};
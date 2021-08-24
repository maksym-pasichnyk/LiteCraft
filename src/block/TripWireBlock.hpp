#pragma once

#include "Block.hpp"

struct TripWireHookBlock;
struct TripWireBlock : Block {
    struct Payload {
        uint16_t powered : 1;
        uint16_t attached : 1;
        uint16_t disarmed : 1;
        uint16_t north : 1;
        uint16_t south : 1;
        uint16_t east : 1;
        uint16_t west : 1;
        uint16_t : 9;
    };

    static constexpr auto POWERED = BlockStateProperty::POWERED;
    static constexpr auto ATTACHED = BlockStateProperty::ATTACHED;
    static constexpr auto DISARMED = BlockStateProperty::DISARMED;
    static constexpr auto NORTH = BlockStateProperty::NORTH;
    static constexpr auto EAST = BlockStateProperty::EAST;
    static constexpr auto SOUTH = BlockStateProperty::SOUTH;
    static constexpr auto WEST = BlockStateProperty::WEST;

    TripWireBlock(int id, TripWireHookBlock* block, Properties properties) : Block(id, std::move(properties)) {}

    void fillStateContainer() override {
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<ATTACHED, get_ATTACHED, set_ATTACHED>();
        bind<DISARMED, get_DISARMED, set_DISARMED>();
        bind<EAST, get_EAST, set_EAST>();
        bind<NORTH, get_NORTH, set_NORTH>();
        bind<SOUTH, get_SOUTH, set_SOUTH>();
        bind<WEST, get_WEST, set_WEST>();
    }

    static auto set_DISARMED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.disarmed = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_ATTACHED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.attached = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_DISARMED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.disarmed == 1;
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }

    static auto get_ATTACHED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.attached == 1;
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
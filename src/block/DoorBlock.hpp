#pragma once

#include "Block.hpp"

struct DoorBlock : Block {
    static constexpr auto FACING = Property::HORIZONTAL_FACING;
    static constexpr auto HALF = Property::DOUBLE_BLOCK_HALF;
    static constexpr auto OPEN = Property::OPEN;
    static constexpr auto HINGE = Property::DOOR_HINGE;
    static constexpr auto POWERED = Property::POWERED;

    using Block::Block;
    
    struct Payload {
        uint16_t facing : 3;
        uint16_t powered : 1;
        uint16_t hinge : 1;
        uint16_t open : 1;
        uint16_t half : 1;
        uint16_t : 9;
    };

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<OPEN, get_OPEN, set_OPEN>();
        bind<HINGE, get_HINGE, set_HINGE>();
        bind<HALF, get_HALF, set_HALF>();
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

    static auto set_HINGE(BlockData state, DoorHingeSide hinge) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.hinge = static_cast<uint16_t>(hinge);
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

    static auto get_HINGE(BlockData state) -> DoorHingeSide {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<DoorHingeSide>(payload.hinge);
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
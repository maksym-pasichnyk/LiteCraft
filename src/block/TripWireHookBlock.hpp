#pragma once

#include "Block.hpp"

struct TripWireHookBlock : Block {
    struct Payload {
        uint16_t facing : 3;
        uint16_t powered : 1;
        uint16_t attached : 1;
        uint16_t : 11;
    };

    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;
    static constexpr auto POWERED = BlockStateProperty::POWERED;
    static constexpr auto ATTACHED = BlockStateProperty::ATTACHED;

    using Block::Block;
    
    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<ATTACHED, get_ATTACHED, set_ATTACHED>();
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

    static auto set_ATTACHED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.attached = flag ? 1 : 0;
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

    static auto get_ATTACHED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.attached == 1;
    }
};
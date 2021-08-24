#pragma once

#include "ContainerBlock.hpp"

struct HopperBlock : ContainerBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t powered : 1;
        uint16_t : 12;
    };

    static constexpr auto FACING = BlockStateProperty::FACING_EXCEPT_UP;
    static constexpr auto ENABLED = BlockStateProperty::ENABLED;

    using ContainerBlock::ContainerBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<ENABLED, get_ENABLED, set_ENABLED>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_ENABLED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_ENABLED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }
};
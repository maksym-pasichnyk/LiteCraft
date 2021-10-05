#pragma once

#include "ContainerBlock.hpp"

struct CommandBlockBlock : ContainerBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t conditional : 1;
        uint16_t : 12;
    };

    static constexpr auto FACING = Property::HORIZONTAL_FACING;
    static constexpr auto CONDITIONAL = Property::CONDITIONAL;

    using ContainerBlock::ContainerBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<CONDITIONAL, get_CONDITIONAL, set_CONDITIONAL>();
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_CONDITIONAL(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.conditional == 1;
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_CONDITIONAL(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.conditional = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
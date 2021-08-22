#pragma once

#include "ContainerBlock.hpp"

struct BeehiveBlock : ContainerBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t honey : 3;
        uint16_t : 10;
    };

    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;
    static constexpr auto HONEY = BlockStateProperty::HONEY_LEVEL;

    using ContainerBlock::ContainerBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<HONEY, get_HONEY, set_HONEY>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_HONEY(BlockData state, int honey) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.honey = honey;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_HONEY(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.honey;
    }
};
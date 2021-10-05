#pragma once

#include "HorizontalBlock.hpp"

struct CocoaBlock : HorizontalBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t age : 2;
        uint16_t : 11;
    };

    static constexpr auto AGE = Property::AGE_0_2;

    using HorizontalBlock::HorizontalBlock;

    void fillStateContainer() override {
        bind<AGE, get_AGE, set_AGE>();
        bind<FACING, get_FACING, set_FACING>();
    }

    static auto get_AGE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.age;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto set_AGE(BlockData state, int age) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.age = age;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};


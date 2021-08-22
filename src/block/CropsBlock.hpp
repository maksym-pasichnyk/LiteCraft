#pragma once

#include "BushBlock.hpp"

struct CropsBlock : BushBlock {
    struct Payload {
        uint16_t age : 3;
        uint16_t : 13;
    };

    static constexpr auto AGE = BlockStateProperty::AGE_0_7;

    using BushBlock::BushBlock;

    void fillStateContainer() override {
        bind<AGE, get_AGE, set_AGE>();
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
};
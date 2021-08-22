#pragma once

#include "AbstractPlantBlock.hpp"

struct AbstractTopPlantBlock : AbstractPlantBlock {
    struct Payload {
        uint16_t age : 5;
        uint16_t : 11;
    };

    static constexpr auto AGE = BlockStateProperty::AGE_0_25;

    using AbstractPlantBlock::AbstractPlantBlock;

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
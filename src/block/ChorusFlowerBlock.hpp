#pragma once

#include "Block.hpp"

struct ChorusPlantBlock;
struct ChorusFlowerBlock : Block {
    struct Payload {
        uint16_t age : 3;
        uint16_t : 13;
    };

    static constexpr auto AGE = BlockStateProperty::AGE_0_5;

    ChorusFlowerBlock(int id, ChorusPlantBlock* block, Properties properties) : Block(id, std::move(properties)) {}
    
    void fillStateContainer() override {
        bind<AGE, get_AGE, set_AGE>();
    }

    static auto get_AGE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<int>(payload.age);
    }

    static auto set_AGE(BlockData state, int age) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.age = static_cast<uint16_t>(age);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
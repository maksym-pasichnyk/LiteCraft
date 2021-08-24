#pragma once

#include "Block.hpp"

struct TargetBlock : Block {
    using Block::Block;
    
    struct Payload {
        uint16_t power : 4;
        uint16_t : 12;
    };

    static constexpr auto POWER = BlockStateProperty::POWER_0_15;

    void fillStateContainer() override {
        bind<POWER, get_POWER, set_POWER>();
    }

    static auto get_POWER(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.power;
    }

    static auto set_POWER(BlockData state, int power) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.power = power;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
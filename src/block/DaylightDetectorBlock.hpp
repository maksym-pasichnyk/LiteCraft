#pragma once

#include "Block.hpp"

struct DaylightDetectorBlock : Block {
    using Block::Block;

    struct Payload {
        uint16_t power : 4;
        uint16_t inverted : 1;
        uint16_t : 11;
    };

    static constexpr auto POWER = BlockStateProperty::POWER_0_15;
    static constexpr auto INVERTED = BlockStateProperty::INVERTED;

    void fillStateContainer() override {
        bind<POWER, get_POWER, set_POWER>();
        bind<INVERTED, get_POWERED, set_POWERED>();
    }

    static auto set_POWER(BlockData state, int power) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.power = static_cast<uint16_t>(power);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.inverted = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_POWER(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<int>(payload.power);
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.inverted == 1;
    }
};
#pragma once

#include "Block.hpp"

struct TurtleEggBlock : Block {
    struct Payload {
        uint16_t hatch : 3;
        uint16_t eggs : 3;
        uint16_t : 10;
    };

    static constexpr auto HATCH = Property::HATCH_0_2;
    static constexpr auto EGGS = Property::EGGS_1_4;

    using Block::Block;

    void fillStateContainer() override {
        bind<HATCH, get_HATCH, set_HATCH>();
        bind<EGGS, get_EGGS, set_EGGS>();
    }

    static auto get_HATCH(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.hatch;
    }

    static auto get_EGGS(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.eggs + 1;
    }

    static auto set_HATCH(BlockData state, int hatch) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.hatch = hatch;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_EGGS(BlockData state, int eggs) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.eggs = eggs - 1;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
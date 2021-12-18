#pragma once

#include "Block.hpp"

enum class Fluids {
    WATER,
    LAVA
};

struct FlowingFluidBlock : Block {
    FlowingFluidBlock(int id, Fluids fluid, BlockBehaviour behaviour) : Block(id, std::move(behaviour)) {}

    struct Payload {
        uint16_t level : 4;
        uint16_t : 12;
    };

    static constexpr auto LEVEL = Property::LEVEL_0_15;

    void fillStateContainer() override {
        bind<LEVEL, get_LEVEL, set_LEVEL>();
    }

    static auto get_LEVEL(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.level;
    }

    static auto set_LEVEL(BlockData state, int level) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.level = level;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
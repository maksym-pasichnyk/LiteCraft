#pragma once

#include "AbstractSignBlock.hpp"

struct StandingSignBlock : AbstractSignBlock {
    struct Payload {
        uint16_t rotation : 8;
        uint16_t : 8;
    };

    static constexpr auto ROTATION = BlockStateProperty::ROTATION_0_15;

    StandingSignBlock(int id, Properties properties, WoodType woodType) : AbstractSignBlock(id, std::move(properties), woodType) {}

    void fillStateContainer() override {
        bind<ROTATION, get_ROTATION, set_ROTATION>();
    }

    static auto get_ROTATION(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.rotation;
    }

    static auto set_ROTATION(BlockData state, int rotation) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.rotation = rotation;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
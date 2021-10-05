#pragma once

#include "Block.hpp"

struct NetherPortalBlock : Block {
    struct Payload {
        uint16_t axis : 2;
        uint16_t : 14;
    };

    using Block::Block;

    static constexpr auto AXIS = Property::HORIZONTAL_AXIS;

    void fillStateContainer() override {
        bind<AXIS, get_AXIS, set_AXIS>();
    }

    static auto get_AXIS(BlockData state) -> DirectionAxis {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<DirectionAxis>(payload.axis);
    }

    static auto set_AXIS(BlockData state, DirectionAxis axis) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.axis = static_cast<uint16_t>(axis);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
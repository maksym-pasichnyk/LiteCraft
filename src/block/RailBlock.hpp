#pragma once

#include "AbstractRailBlock.hpp"

struct RailBlock : AbstractRailBlock {
    struct Payload {
        uint16_t shape : 4;
        uint16_t : 12;
    };

    static constexpr auto SHAPE = BlockStateProperty::RAIL_SHAPE;

    using AbstractRailBlock::AbstractRailBlock;

    void fillStateContainer() override {
        bind<SHAPE, get_SHAPE, set_SHAPE>();
    }

    static auto get_SHAPE(BlockData state) -> RailShape {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<RailShape>(payload.shape);
    }

    static auto set_SHAPE(BlockData state, RailShape shape) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.shape = static_cast<uint16_t>(shape);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
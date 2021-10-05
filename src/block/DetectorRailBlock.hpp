#pragma once

#include "AbstractRailBlock.hpp"

struct DetectorRailBlock : AbstractRailBlock {
    using AbstractRailBlock::AbstractRailBlock;

    static constexpr auto SHAPE = Property::RAIL_SHAPE_STRAIGHT;
    static constexpr auto POWERED = Property::POWERED;

    struct Payload {
        uint16_t shape : 4;
        uint16_t powered : 1;
        uint16_t : 11;
    };

    void fillStateContainer() override {
        bind<SHAPE, get_SHAPE, set_SHAPE>();
        bind<POWERED, get_POWERED, set_POWERED>();
    }
    
    static auto set_SHAPE(BlockData state, RailShape shape) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.shape = static_cast<uint16_t>(shape);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_SHAPE(BlockData state) -> RailShape {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<RailShape>(payload.shape);
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }
};
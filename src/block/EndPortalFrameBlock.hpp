#pragma once

#include "Block.hpp"

struct EndPortalFrameBlock : Block {
    struct Payload {
        uint16_t facing : 3;
        uint16_t eye : 1;
        uint16_t : 12;
    };

    static constexpr auto FACING = Property::HORIZONTAL_FACING;
    static constexpr auto EYE = Property::EYE;

    using Block::Block;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<EYE, get_EYE, set_EYE>();
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_EYE(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.eye == 1;
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_EYE(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.eye = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
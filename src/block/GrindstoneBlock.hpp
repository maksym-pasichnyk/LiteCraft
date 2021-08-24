#pragma once

#include "HorizontalFaceBlock.hpp"

struct GrindstoneBlock : HorizontalFaceBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t face : 2;
        uint16_t : 11;
    };

    using HorizontalFaceBlock::HorizontalFaceBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<FACE, get_FACE, set_FACE>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_FACE(BlockData state, AttachFace face) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.face = static_cast<uint16_t>(face);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_FACE(BlockData state) -> AttachFace {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<AttachFace>(payload.face);
    }
};
#pragma once

#include "HorizontalFaceBlock.hpp"

struct LeverBlock : HorizontalFaceBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t powered : 1;
        uint16_t face : 2;
        uint16_t : 10;
    };

    static constexpr auto POWERED = BlockStateProperty::POWERED;

    using HorizontalFaceBlock::HorizontalFaceBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<FACE, get_FACE, set_FACE>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
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

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }

    static auto get_FACE(BlockData state) -> AttachFace {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<AttachFace>(payload.face);
    }
};
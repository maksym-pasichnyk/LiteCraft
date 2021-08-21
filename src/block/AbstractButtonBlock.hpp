#pragma once

#include "HorizontalFaceBlock.hpp"

struct AbstractButtonBlock : HorizontalFaceBlock {
    static constexpr auto POWERED = BlockStateProperty::POWERED;

    using HorizontalFaceBlock::HorizontalFaceBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<FACE, get_FACE, set_FACE>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        return state;
    }

    static auto set_POWERED(BlockData state, bool powered) -> BlockData {
        return state;
    }

    static auto set_FACE(BlockData state, AttachFace face) -> BlockData {
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        return Direction::NORTH;
    }

    static auto get_POWERED(BlockData state) -> bool {
        return false;
    }

    static auto get_FACE(BlockData state) -> AttachFace {
        return AttachFace::FLOOR;
    }
};
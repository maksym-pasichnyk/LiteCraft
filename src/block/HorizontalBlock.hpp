#pragma once

#include "Block.hpp"
#include <util/Mirror.hpp>
#include <util/Rotation.hpp>

struct HorizontalBlock : Block {
    static constexpr auto FACING = Property::HORIZONTAL_FACING;

    using Block::Block;

    auto rotate(BlockData state, Rotation rotation) -> BlockData override {
        return state.set<FACING>(RotationUtil::rotate(rotation, state.get<FACING>()));
    }

    auto mirror(BlockData state, Mirror mirror) -> BlockData override {
        return rotate(state, MirrorUtil::toRotation(mirror, state.get<FACING>()));
    }
};
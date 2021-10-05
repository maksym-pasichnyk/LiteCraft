#pragma once

#include "AbstractBlock.hpp"
#include "BlockData.hpp"
#include <util/Mirror.hpp>
#include <util/Rotation.hpp>
#include <state/BlockStateProperties.hpp>

struct Block : AbstractBlock {
    BlockData baseState;
    BlockData defaultState;

    explicit Block(int id, BlockBehaviour behaviour) : AbstractBlock(id, std::move(behaviour)) {
        baseState = {static_cast<uint16_t>(id), 0};
        setDefaultState(baseState);
    }

    void setDefaultState(BlockData state) {
        defaultState = state;
    }

    auto getDefaultState() -> BlockData {
        return defaultState;
    }

    bool in(const BlockTag &tag) const {
        return tag.items.contains(this);
    }

    auto getStateWithMeta(int meta) -> BlockData {
        return {static_cast<uint16_t>(id), static_cast<uint16_t>(meta)};
    }

    virtual void fillStateContainer() {}

    virtual auto rotate(BlockData state, Rotation rotation) -> BlockData {
        return state;
    }

    virtual auto mirror(BlockData state, Mirror mirror) -> BlockData {
        return state;
    }
};
#pragma once

#include "AbstractBlock.hpp"
#include "BlockData.hpp"

struct Block : AbstractBlock {
    BlockData baseState;
    BlockData defaultState;

    explicit Block(int id, Properties properties) : AbstractBlock(id, std::move(properties)) {
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
};
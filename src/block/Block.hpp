#pragma once

#include "AbstractBlock.hpp"
#include "BlockData.hpp"

struct Block : AbstractBlock {
    explicit Block(int id, Properties properties) : AbstractBlock(id, std::move(properties)) {}

    auto getDefaultState() -> BlockData {
        return {static_cast<uint16_t>(id), 0};
    }

    auto getStateWithMeta(int meta) -> BlockData {
        return {static_cast<uint16_t>(id), static_cast<uint16_t>(meta)};
    }

    virtual void fillStateContainer() {}
};
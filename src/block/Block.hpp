#pragma once

#include "AbstractBlock.hpp"
#include "BlockData.hpp"
#include <util/Mirror.hpp>
#include <util/Rotation.hpp>
#include <state/BlockStateProperties.hpp>

struct Block : AbstractBlock {
    BlockData baseState;
    BlockData defaultState;
    std::vector<BlockData> validStates;

    explicit Block(int id, BlockBehaviour behaviour) : AbstractBlock(id, std::move(behaviour)) {
        baseState = {static_cast<uint16_t>(id), 0};
        defaultState = baseState;
    }

    auto getDefaultState() -> BlockData {
        return defaultState;
    }

    auto in(const BlockTag &tag) const -> bool {
        return tag.contains(this);
    }

    virtual void fillStateContainer() {}

    virtual auto rotate(BlockData state, Rotation rotation) -> BlockData {
        return state;
    }

    virtual auto mirror(BlockData state, Mirror mirror) -> BlockData {
        return state;
    }

    void fillStatesRecursive(std::span<const Property> props, BlockData state) {
        if (props.size() > 1) {
            for (auto&& value : PropertyUtil::values(props[0])) {
                fillStatesRecursive(props.subspan(1), state.set(props[0], value));
            }
        } else {
            for (auto&& value : PropertyUtil::values(props[0])) {
                validStates.emplace_back(state.set(props[0], value));
            }
        }
    }

    void fillValidStates() {
        validStates.clear();

        const auto props = ranges::to_vector(ranges::views::values(properties));
        if (!props.empty()) {
            fillStatesRecursive(props, getDefaultState());
        }
    }
};
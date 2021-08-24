#pragma once

#include "Block.hpp"

struct ScaffoldingBlock : Block {
    struct Payload {
        uint16_t distance : 3;
        uint16_t bottom : 1;
        uint16_t face : 1;
        uint16_t : 11;
    };

    static constexpr auto DISTANCE = BlockStateProperty::DISTANCE_0_7;
    static constexpr auto BOTTOM = BlockStateProperty::BOTTOM;

    using Block::Block;

    void fillStateContainer() override {
        bind<DISTANCE, get_DISTANCE, set_DISTANCE>();
        bind<BOTTOM, get_BOTTOM, set_BOTTOM>();
    }

    static auto set_DISTANCE(BlockData state, int distance) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.distance = static_cast<uint16_t>(distance);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_BOTTOM(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.bottom = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_DISTANCE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<int>(payload.distance);
    }

    static auto get_BOTTOM(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.bottom == 1;
    }
};
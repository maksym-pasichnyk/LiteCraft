#pragma once

#include "Block.hpp"

struct LeavesBlock : Block {
    using Block::Block;

    struct Payload {
        uint16_t distance : 3;
        uint16_t persistent : 1;
        uint16_t : 12;
    };

    static constexpr auto DISTANCE = Property::DISTANCE_1_7;
    static constexpr auto PERSISTENT = Property::PERSISTENT;

    void fillStateContainer() override {
        bind<DISTANCE, get_DISTANCE, set_DISTANCE>();
        bind<PERSISTENT, get_PERSISTENT, set_PERSISTENT>();
    }

    static auto get_DISTANCE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.distance;
    }


    static auto get_PERSISTENT(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.persistent == 1;
    }

    static auto set_DISTANCE(BlockData state, int distance) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.distance = distance;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_PERSISTENT(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.distance = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
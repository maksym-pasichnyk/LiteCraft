#pragma once

#include "Block.hpp"

struct FarmlandBlock : Block {
    struct Payload {
        uint16_t stage : 3;
        uint16_t : 13;
    };

    static constexpr auto MOISTURE = BlockStateProperty::MOISTURE_0_7;

    using Block::Block;

    void fillStateContainer() override {
        bind<MOISTURE, get_MOISTURE, set_MOISTURE>();
    }

    static auto get_MOISTURE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.stage;
    }

    static auto set_MOISTURE(BlockData state, int stage) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.stage = stage;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
#pragma once

#include "Block.hpp"

struct JigsawBlock : Block {
    using Block::Block;

    struct Payload {
        uint16_t orientation : 1;
        uint16_t : 15;
    };

    static constexpr auto ORIENTATION = BlockStateProperty::ORIENTATION;

    void fillStateContainer() override {
        bind<ORIENTATION, get_ORIENTATION, set_ORIENTATION>();
    }

    static auto get_ORIENTATION(BlockData state) -> JigsawOrientation {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<JigsawOrientation>(payload.orientation);
    }

    static auto set_ORIENTATION(BlockData state, JigsawOrientation orientation) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.orientation = static_cast<uint16_t>(orientation);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
#pragma once

#include "Block.hpp"

struct SlabBlock : Block {
    using Block::Block;
    
    struct Payload {
        uint16_t type : 2;
        uint16_t : 14;
    };

    static constexpr auto TYPE = BlockStateProperty::SLAB_TYPE;

    void fillStateContainer() override {
        bind<TYPE, get_TYPE, set_TYPE>();
    }

    static auto set_TYPE(BlockData state, SlabType type) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.type = static_cast<uint16_t>(type);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_TYPE(BlockData state) -> SlabType {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<SlabType>(payload.type);
    }
};
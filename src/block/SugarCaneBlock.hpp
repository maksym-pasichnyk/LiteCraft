#pragma once

#include "Block.hpp"

struct SugarCaneBlock : Block {
    struct Payload {
        uint16_t age : 4;
        uint16_t : 12;
    };

    static constexpr auto AGE = Property::AGE_0_15;

    using Block::Block;

    void fillStateContainer() override {
        bind<AGE, get_AGE, set_AGE>();
    }

    static auto get_AGE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.age;
    }

    static auto set_AGE(BlockData state, int age) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.age = age;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    bool isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;
};
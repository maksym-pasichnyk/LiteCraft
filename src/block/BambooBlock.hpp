#pragma once

#include "Block.hpp"

struct BambooBlock : Block {
    struct Payload {
        uint16_t age : 1;
        uint16_t stage : 1;
        uint16_t leaves : 2;
        uint16_t : 12;
    };

    static constexpr auto AGE = Property::AGE_0_1;
    static constexpr auto LEAVES = Property::BAMBOO_LEAVES;
    static constexpr auto STAGE = Property::STAGE_0_1;

    using Block::Block;

    bool isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;

    void fillStateContainer() override {
        bind<AGE, get_AGE, set_AGE>();
        bind<LEAVES, get_LEAVES, set_LEAVES>();
        bind<STAGE, get_STAGE, set_STAGE>();
    }

    static auto get_AGE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.age;
    }

    static auto get_LEAVES(BlockData state) -> BambooLeaves {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<BambooLeaves>(payload.leaves);
    }

    static auto get_STAGE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.stage;
    }

    static auto set_AGE(BlockData state, int age) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.age = age;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_LEAVES(BlockData state, BambooLeaves leaves) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.leaves = static_cast<uint16_t>(leaves);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_STAGE(BlockData state, int stage) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.stage = stage;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

};
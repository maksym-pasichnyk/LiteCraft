#pragma once

#include "BushBlock.hpp"

struct Tree {
    virtual ~Tree() = default;
};
struct OakTree : Tree {};
struct SpruceTree : Tree {};
struct BirchTree : Tree {};
struct JungleTree : Tree {};
struct AcaciaTree : Tree {};
struct DarkOakTree : Tree {};

struct SaplingBlock : BushBlock {
    SaplingBlock(int id, Tree* tree, BlockBehaviour behaviour) : BushBlock(id, std::move(behaviour)) {}
    
    struct Payload {
        uint16_t stage : 1;
        uint16_t : 15;
    };

    static constexpr auto STAGE = Property::STAGE_0_1;

    using BushBlock::BushBlock;

    void fillStateContainer() override {
        bind<STAGE, get_STAGE, set_STAGE>();
    }

    static auto get_STAGE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.stage;
    }

    static auto set_STAGE(BlockData state, int stage) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.stage = stage;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
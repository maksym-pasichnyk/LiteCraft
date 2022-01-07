#pragma once

#include "BushBlock.hpp"

struct SeaPickleBlock : BushBlock {
    struct Payload {
        uint16_t pickles : 2;
        uint16_t waterlogged : 1;
        uint16_t : 13;
    };

    static constexpr auto PICKLES = Property::PICKLES_1_4;
    static constexpr auto WATERLOGGED = Property::WATERLOGGED;

    using BushBlock::BushBlock;

    void fillStateContainer() override {
        bind<PICKLES, get_PICKLES, set_PICKLES>();
        bind<WATERLOGGED, get_WATERLOGGED, set_WATERLOGGED>();
    }

    static auto get_PICKLES(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.pickles + 1;
    }

    static auto set_PICKLES(BlockData state, int pickles) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.pickles = static_cast<uint16_t>(pickles - 1);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_WATERLOGGED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.pickles == 1;
    }

    static auto set_WATERLOGGED(BlockData state, bool waterlogged) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.waterlogged = waterlogged ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
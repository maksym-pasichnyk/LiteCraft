#pragma once

#include "DirectionalBlock.hpp"

struct PistonBlock : DirectionalBlock {
    PistonBlock(int id, bool sticky, BlockBehaviour behaviour) : DirectionalBlock(id, std::move(behaviour)) {}

    struct Payload {
        uint16_t facing : 3;
        uint16_t extended : 1;
        uint16_t : 12;
    };

    static constexpr auto EXTENDED = Property::EXTENDED;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<EXTENDED, get_EXTENDED, set_EXTENDED>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_EXTENDED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.extended = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_EXTENDED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.extended == 1;
    }
};
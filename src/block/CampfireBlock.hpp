#pragma once

#include "ContainerBlock.hpp"

struct CampfireBlock : ContainerBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t lit : 1;
        uint16_t signal_fire : 1;
        uint16_t : 11;
    };

    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;
    static constexpr auto LIT = BlockStateProperty::LIT;
    static constexpr auto SIGNAL_FIRE = BlockStateProperty::SIGNAL_FIRE;

    CampfireBlock(int id, bool smokey, int fireDamage, Properties properties) : ContainerBlock(id, std::move(properties)) {}
    
    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<LIT, get_LIT, set_LIT>();
        bind<SIGNAL_FIRE, get_SIGNAL_FIRE, set_SIGNAL_FIRE>();
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_LIT(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.lit == 1;
    }

    static auto get_SIGNAL_FIRE(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.signal_fire == 1;
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_LIT(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.lit = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_SIGNAL_FIRE(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.signal_fire = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
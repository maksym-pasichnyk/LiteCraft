#pragma once

#include "ContainerBlock.hpp"

struct BrewingStandBlock : ContainerBlock {
    struct Payload {
        uint16_t bottle_0 : 1;
        uint16_t bottle_1 : 1;
        uint16_t bottle_2 : 1;
        uint16_t : 13;
    };

    static constexpr auto HAS_BOTTLE = std::array{
        BlockStateProperty::HAS_BOTTLE_0,
        BlockStateProperty::HAS_BOTTLE_1,
        BlockStateProperty::HAS_BOTTLE_2
    };

    using ContainerBlock::ContainerBlock;
    
    void fillStateContainer() override {
        bind<HAS_BOTTLE[0], get_BOTTLE_0, set_BOTTLE_0>();
        bind<HAS_BOTTLE[1], get_BOTTLE_1, set_BOTTLE_1>();
        bind<HAS_BOTTLE[2], get_BOTTLE_2, set_BOTTLE_2>();
    }

    static auto set_BOTTLE_0(BlockData state, bool bottle) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.bottle_0 = bottle ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_BOTTLE_1(BlockData state, bool bottle) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.bottle_1 = bottle ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_BOTTLE_2(BlockData state, bool bottle) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.bottle_2 = bottle ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_BOTTLE_0(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.bottle_0 == 1;
    }

    static auto get_BOTTLE_1(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.bottle_1 == 1;
    }

    static auto get_BOTTLE_2(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.bottle_2 == 1;
    }
};
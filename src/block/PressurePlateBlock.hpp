#pragma once

#include "AbstractPressurePlateBlock.hpp"

struct PressurePlateBlock : AbstractPressurePlateBlock {
    enum class Sensitivity {
        EVERYTHING,
        MOBS
    };

    PressurePlateBlock(int id, Sensitivity sensitivity, Properties properties) : AbstractPressurePlateBlock(id, std::move(properties)) {}

    struct Payload {
        uint16_t powered : 1;
        uint16_t : 15;
    };

    static constexpr auto POWERED = BlockStateProperty::POWERED;

    void fillStateContainer() override {
        bind<POWERED, get_POWERED, set_POWERED>();
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }
};
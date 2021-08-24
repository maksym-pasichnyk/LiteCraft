#pragma once

#include "RedstoneDiodeBlock.hpp"

struct ComparatorBlock : RedstoneDiodeBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t powered : 1;
        uint16_t mode : 1;
        uint16_t : 11;
    };

    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;
    static constexpr auto POWERED = BlockStateProperty::POWERED;
    static constexpr auto MODE = BlockStateProperty::COMPARATOR_MODE;

    using RedstoneDiodeBlock::RedstoneDiodeBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<MODE, get_MODE, set_MODE>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_MODE(BlockData state, ComparatorMode mode) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.mode = static_cast<uint16_t>(mode);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }

    static auto get_MODE(BlockData state) -> ComparatorMode {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<ComparatorMode>(payload.mode);
    }
};
#pragma once

#include "AbstractChestBlock.hpp"

struct ChestBlock : AbstractChestBlock {
    using AbstractChestBlock::AbstractChestBlock;

    struct Payload {
        uint16_t facing : 3;
        uint16_t type : 3;
        uint16_t : 10;
    };

    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;
    static constexpr auto TYPE = BlockStateProperty::CHEST_TYPE;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<TYPE, get_TYPE, set_TYPE>();
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_TYPE(BlockData state) -> ChestType {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<ChestType>(payload.facing);
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_TYPE(BlockData state, ChestType type) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.type = static_cast<uint16_t>(type);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
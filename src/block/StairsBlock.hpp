#pragma once

#include "Block.hpp"

struct StairsBlock : Block {
    struct Payload {
        uint16_t facing : 3;
        uint16_t shape : 3;
        uint16_t half : 1;
        uint16_t : 9;
    };

    static constexpr auto HALF = BlockStateProperty::HALF;
    static constexpr auto SHAPE = BlockStateProperty::STAIRS_SHAPE;
    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;

    StairsBlock(int id, BlockData data, Properties properties) : Block(id, std::move(properties)) {}

    void fillStateContainer() override {
        bind<HALF, get_HALF, set_HALF>();
        bind<SHAPE, get_SHAPE, set_SHAPE>();
        bind<FACING, get_FACING, set_FACING>();
    }

    static auto get_HALF(BlockData state) -> Half {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Half>(payload.half);
    }

    static auto get_SHAPE(BlockData state) -> StairsShape {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<StairsShape>(payload.shape);
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto set_HALF(BlockData state, Half half) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.half = static_cast<uint16_t>(half);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_SHAPE(BlockData state, StairsShape shape) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.shape = static_cast<uint16_t>(shape);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
#pragma once

#include "../particles/ParticleType.hpp"
#include "TorchBlock.hpp"

struct WallTorchBlock : TorchBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t : 13;
    };

    static constexpr auto FACING = BlockStateProperty::HORIZONTAL_FACING;

    WallTorchBlock(int id, Properties properties, ParticleType particleType) : TorchBlock(id, std::move(properties), particleType) {}

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
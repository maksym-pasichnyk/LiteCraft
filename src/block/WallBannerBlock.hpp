#pragma once

#include "AbstractBannerBlock.hpp"
#include "material/DyeColors.hpp"

struct WallBannerBlock : AbstractBannerBlock {
    struct Payload {
        uint16_t facing : 3;
        uint16_t : 13;
    };

    static constexpr auto FACING = Property::HORIZONTAL_FACING;

    WallBannerBlock(int id, DyeColors color, BlockBehaviour behaviour) : AbstractBannerBlock(id, std::move(behaviour)) {}

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
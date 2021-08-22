#pragma once

#include "AbstractBannerBlock.hpp"
#include "material/DyeColors.hpp"

struct BannerBlock : AbstractBannerBlock {
    struct Payload {
        uint16_t rotation : 8;
        uint16_t : 8;
    };

    static constexpr auto ROTATION = BlockStateProperty::ROTATION_0_15;

    BannerBlock(int id, DyeColors color, Properties properties) : AbstractBannerBlock(id, std::move(properties)) {}

    void fillStateContainer() override {
        bind<ROTATION, get_ROTATION, set_ROTATION>();
    }

    static auto get_ROTATION(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.rotation;
    }

    static auto set_ROTATION(BlockData state, int rotation) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.rotation = rotation;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
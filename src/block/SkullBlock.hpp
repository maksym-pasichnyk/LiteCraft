#pragma once

#include "AbstractSkullBlock.hpp"

struct SkullBlock : AbstractSkullBlock {
    enum class Type {
        SKELETON,
        WITHER_SKELETON,
        PLAYER,
        ZOMBIE,
        CREEPER,
        DRAGON
    };

    struct Payload {
        uint16_t rotation : 3;
        uint16_t : 12;
    };

    static constexpr auto ROTATION = Property::ROTATION_0_15;

    SkullBlock(int id, Type type, BlockBehaviour behaviour) : AbstractSkullBlock(id, std::move(behaviour)) {}

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
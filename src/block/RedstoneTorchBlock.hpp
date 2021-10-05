#pragma once

#include "TorchBlock.hpp"

struct RedstoneTorchBlock : TorchBlock {
    RedstoneTorchBlock(int id, BlockBehaviour behaviour) : TorchBlock(id, std::move(behaviour), ParticleType::REDSTONE_DUST) {}

    struct Payload {
        uint16_t lit : 1;
        uint16_t : 15;
    };

    static constexpr auto LIT = Property::LIT;

    void fillStateContainer() override {
        bind<LIT, get_LIT, set_LIT>();
    }

    static auto get_LIT(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.lit == 1;
    }

    static auto set_LIT(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.lit = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
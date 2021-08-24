#pragma once

#include "Block.hpp"

struct SnowBlock : Block {
    struct Payload {
        uint16_t layers : 3;
        uint16_t : 13;
    };

    static constexpr auto LAYERS = BlockStateProperty::LAYERS_1_8;

    using Block::Block;

    void fillStateContainer() override {
        bind<LAYERS, get_LAYERS, set_LAYERS>();
    }

    static auto get_LAYERS(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.layers;
    }

    static auto set_LAYERS(BlockData state, int layers) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.layers = static_cast<uint16_t>(layers);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    bool isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) override;

    RenderType getRenderType() const override {
        return RenderType::SnowLayer;
    }
};
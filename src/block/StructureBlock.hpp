#pragma once

#include "ContainerBlock.hpp"

struct StructureBlock : ContainerBlock {
    struct Payload {
        uint16_t mode : 2;
        uint16_t : 14;
    };

    static constexpr auto MODE = BlockStateProperty::STRUCTURE_BLOCK_MODE;

    using ContainerBlock::ContainerBlock;

    void fillStateContainer() override {
        bind<MODE, get_MODE, set_MODE>();
    }

    static auto set_MODE(BlockData state, StructureMode mode) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.mode = static_cast<uint16_t>(mode);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_MODE(BlockData state) -> StructureMode {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<StructureMode>(payload.mode);
    }
};
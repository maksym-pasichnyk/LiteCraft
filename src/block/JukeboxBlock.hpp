#pragma once

#include "ContainerBlock.hpp"

struct JukeboxBlock : ContainerBlock {
    using ContainerBlock::ContainerBlock;

    struct Payload {
        uint16_t record : 1;
        uint16_t : 15;
    };

    static constexpr auto RECORD = BlockStateProperty::HAS_RECORD;

    void fillStateContainer() override {
        bind<RECORD, get_RECORD, set_RECORD>();
    }

    static auto get_RECORD(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.record == 1;
    }

    static auto set_RECORD(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.record = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }
};
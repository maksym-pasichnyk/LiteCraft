#pragma once

#include "ContainerBlock.hpp"

struct BellBlock : ContainerBlock {
    struct Payload {
        uint16_t attachment : 2;
        uint16_t facing : 3;
        uint16_t : 2;
        uint16_t powered : 1;
        uint16_t : 8;
    };

    static constexpr auto FACING = Property::HORIZONTAL_FACING;
    static constexpr auto POWERED = Property::POWERED;
    static constexpr auto ATTACHMENT = Property::BELL_ATTACHMENT;

    using ContainerBlock::ContainerBlock;

    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<ATTACHMENT, get_ATTACHMENT, set_ATTACHMENT>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_ATTACHMENT(BlockData state, BellAttachment attachment) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.attachment = static_cast<uint16_t>(attachment);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }

    static auto get_ATTACHMENT(BlockData state) -> BellAttachment {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<BellAttachment>(payload.attachment);
    }
};
#pragma once

#include "HorizontalBlock.hpp"

struct BedBlock : HorizontalBlock {
    struct Payload {
        uint16_t part : 2;
        uint16_t facing : 3;
        uint16_t : 2;
        uint16_t occupied : 1;
        uint16_t : 8;
    };

    static constexpr auto PART = BlockStateProperty::BED_PART;
    static constexpr auto OCCUPIED = BlockStateProperty::OCCUPIED;

    BedBlock(int id, DyeColors color, Properties properties) : HorizontalBlock(id, std::move(properties)) {}
    
    void fillStateContainer() override {
        bind<FACING, get_FACING, set_FACING>();
        bind<OCCUPIED, get_OCCUPIED, set_OCCUPIED>();
        bind<PART, get_PART, set_PART>();
    }

    static auto set_FACING(BlockData state, Direction facing) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.facing = static_cast<uint16_t>(facing);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_OCCUPIED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.occupied = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_PART(BlockData state, BedPart part) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.part = static_cast<uint16_t>(part);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_FACING(BlockData state) -> Direction {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<Direction>(payload.facing);
    }

    static auto get_OCCUPIED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.occupied == 1;
    }

    static auto get_PART(BlockData state) -> BedPart {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<BedPart>(payload.part);
    }
};
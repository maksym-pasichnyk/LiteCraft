#pragma once

#include "Block.hpp"

struct NoteBlock : Block {
    using Block::Block;

    struct Payload {
        uint16_t instrument : 4;
        uint16_t powered : 1;
        uint16_t note : 5;
        uint16_t : 6;
    };

    static constexpr auto NOTE = BlockStateProperty::NOTE_0_24;
    static constexpr auto POWERED = BlockStateProperty::POWERED;
    static constexpr auto INSTRUMENT = BlockStateProperty::NOTE_BLOCK_INSTRUMENT;

    void fillStateContainer() override {
        bind<INSTRUMENT, get_INSTRUMENT, set_INSTRUMENT>();
        bind<POWERED, get_POWERED, set_POWERED>();
        bind<NOTE, get_NOTE, set_NOTE>();
    }

    static auto set_INSTRUMENT(BlockData state, NoteBlockInstrument instrument) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.instrument = static_cast<uint16_t>(instrument);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_POWERED(BlockData state, bool flag) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.powered = flag ? 1 : 0;
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto set_NOTE(BlockData state, int note) -> BlockData {
        auto payload = std::bit_cast<Payload>(state.dv);
        payload.note = static_cast<uint16_t>(note);
        state.dv = std::bit_cast<uint16_t>(payload);
        return state;
    }

    static auto get_INSTRUMENT(BlockData state) -> NoteBlockInstrument {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<NoteBlockInstrument>(payload.instrument);
    }

    static auto get_POWERED(BlockData state) -> bool {
        auto payload = std::bit_cast<Payload>(state.dv);
        return payload.powered == 1;
    }

    static auto get_NOTE(BlockData state) -> int {
        auto payload = std::bit_cast<Payload>(state.dv);
        return static_cast<int>(payload.note);
    }
};
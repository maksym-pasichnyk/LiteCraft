#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <ranges>

struct PaletteEntry {
    std::string name;
    uint16_t val;
};

struct BlockStorage {
    std::vector<uint16_t> blocks;
    std::vector<PaletteEntry> palette;
};

struct Subchunk {
    std::vector<BlockStorage> block_storages;
};
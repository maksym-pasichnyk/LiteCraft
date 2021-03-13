#pragma once

#include <memory>

struct ChunkGenerator;

struct Dimension {
    std::unique_ptr<ChunkGenerator> generator;
};
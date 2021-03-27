#pragma once

#include "Block.hpp"

struct PressurePlateBlock : Block {
    enum class Sensitivity {
        EVERYTHING,
        MOBS
    };

    PressurePlateBlock(int id, Sensitivity sensitivity, Properties properties) : Block(id, std::move(properties)) {

    }
};
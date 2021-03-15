#pragma once

#include "CaveWorldCarver.hpp"

struct NetherCaveCarver : CaveWorldCarver {
    NetherCaveCarver() : CaveWorldCarver(128) {}
};
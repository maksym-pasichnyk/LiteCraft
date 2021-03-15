#include "WorldCarver.hpp"

#include "CaveWorldCarver.hpp"
#include "NetherCaveCarver.hpp"
#include "CanyonWorldCarver.hpp"
#include "UnderwaterCanyonWorldCarver.hpp"
#include "UnderwaterCaveWorldCarver.hpp"

std::unique_ptr<WorldCarver> WorldCarver::CAVE = nullptr;
std::unique_ptr<WorldCarver> WorldCarver::NETHER_CAVE = nullptr;
std::unique_ptr<WorldCarver> WorldCarver::CANYON = nullptr;
std::unique_ptr<WorldCarver> WorldCarver::UNDERWATER_CANYON = nullptr;
std::unique_ptr<WorldCarver> WorldCarver::UNDERWATER_CAVE = nullptr;

void WorldCarver::registerCarvers() {
    CAVE = std::make_unique<CaveWorldCarver>(256);
    NETHER_CAVE = std::make_unique<NetherCaveCarver>();
    CANYON = std::make_unique<CanyonWorldCarver>();
    UNDERWATER_CANYON = std::make_unique<UnderwaterCanyonWorldCarver>();
    UNDERWATER_CAVE = std::make_unique<UnderwaterCaveWorldCarver>();
}

WorldCarver::WorldCarver(int32_t maxHeight) : maxHeight{maxHeight} {
    carvableBlocks = {};
    carvableFluids = {};
}

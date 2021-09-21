#include "Carvers.hpp"
#include "CaveWorldCarver.hpp"
#include "NetherCaveCarver.hpp"
#include "CanyonWorldCarver.hpp"
#include "UnderwaterCanyonWorldCarver.hpp"
#include "UnderwaterCaveWorldCarver.hpp"

Registry<WorldCarver> Carvers::carvers{};

void Carvers::init() {
    create<CaveWorldCarver>("cave", 256);
    create<NetherCaveCarver>("nether_cave");
    create<CanyonWorldCarver>("canyon");
//    create<UnderwaterCanyonWorldCarver>("underwater_canyon");
//    create<UnderwaterCaveWorldCarver>("underwater_cave");
}
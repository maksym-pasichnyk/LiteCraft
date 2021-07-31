#include "Carvers.hpp"
#include "CaveWorldCarver.hpp"
#include "NetherCaveCarver.hpp"
#include "CanyonWorldCarver.hpp"
#include "UnderwaterCanyonWorldCarver.hpp"
#include "UnderwaterCaveWorldCarver.hpp"

Registry<WorldCarver> Carvers::carvers{};
WorldCarver* Carvers::CAVE;
WorldCarver* Carvers::NETHER_CAVE;
WorldCarver* Carvers::CANYON;
//WorldCarver* Carvers::UNDERWATER_CANYON;
//WorldCarver* Carvers::UNDERWATER_CAVE;

template <typename T, typename... Args>
static T* registerCarver(std::string name, Args&&... args) {
    return dynamic_cast<T*>(Carvers::carvers.add(std::move(name), std::make_unique<T>(std::forward<Args>(args)...)));
}

void Carvers::registerCarvers() {
    CAVE = registerCarver<CaveWorldCarver>("cave", 256);
    NETHER_CAVE = registerCarver<NetherCaveCarver>("nether_cave");
    CANYON = registerCarver<CanyonWorldCarver>("canyon");
//    UNDERWATER_CANYON = registerCarver<UnderwaterCanyonWorldCarver>();
//    UNDERWATER_CAVE = registerCarver<UnderwaterCaveWorldCarver>();
}
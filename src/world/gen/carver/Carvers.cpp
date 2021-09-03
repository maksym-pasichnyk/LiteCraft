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
static auto create(std::string name, Args&&... args) -> T* {
    return dynamic_cast<T*>(Carvers::carvers.add(std::move(name), std::make_unique<T>(std::forward<Args>(args)...)));
}

void Carvers::registerCarvers() {
    CAVE = create<CaveWorldCarver>("cave", 256);
    NETHER_CAVE = create<NetherCaveCarver>("nether_cave");
    CANYON = create<CanyonWorldCarver>("canyon");
//    UNDERWATER_CANYON = create<UnderwaterCanyonWorldCarver>();
//    UNDERWATER_CAVE = create<UnderwaterCaveWorldCarver>();
}
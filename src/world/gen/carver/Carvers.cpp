#include "Carvers.hpp"
#include "CaveWorldCarver.hpp"
#include "NetherCaveCarver.hpp"
#include "CanyonWorldCarver.hpp"
#include "UnderwaterCanyonWorldCarver.hpp"
#include "UnderwaterCaveWorldCarver.hpp"

std::vector<std::unique_ptr<WorldCarver>> Carvers::carvers{};
std::map<std::string, WorldCarver*> Carvers::registry{};
WorldCarver* Carvers::CAVE;
WorldCarver* Carvers::NETHER_CAVE;
WorldCarver* Carvers::CANYON;
//WorldCarver* Carvers::UNDERWATER_CANYON;
//WorldCarver* Carvers::UNDERWATER_CAVE;

template <typename T, typename... Args>
static T* registerCarver(std::string name, Args&&... args) {
    auto carver = Carvers::carvers.emplace_back(std::make_unique<T>(std::forward<Args>(args)...)).get();
    Carvers::registry.emplace(std::move(name), carver);
    return dynamic_cast<T*>(carver);
}

void Carvers::registerCarvers() {
    CAVE = registerCarver<CaveWorldCarver>("cave", 256);
    NETHER_CAVE = registerCarver<NetherCaveCarver>("nether_cave");
    CANYON = registerCarver<CanyonWorldCarver>("canyon");
//    UNDERWATER_CANYON = registerCarver<UnderwaterCanyonWorldCarver>();
//    UNDERWATER_CAVE = registerCarver<UnderwaterCaveWorldCarver>();
}
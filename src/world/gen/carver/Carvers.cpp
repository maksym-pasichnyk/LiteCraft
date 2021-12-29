#include "Carvers.hpp"
#include "CaveWorldCarver.hpp"
#include "NetherCaveCarver.hpp"
#include "CanyonWorldCarver.hpp"

#include <Json.hpp>

Registry<WorldCarver> Carvers::carvers{};

template<>
auto Json::From<WorldCarver*>::from(WorldCarver* const& carver) -> Self {
    return Carvers::carvers.name(carver).value();
}

template<>
auto Json::Into<WorldCarver*>::into(const Self& obj) -> Result {
    return Carvers::carvers.get(obj.as_string().value());
}

void Carvers::init() {
    create<CaveWorldCarver>("cave", 256);
    create<NetherCaveCarver>("nether_cave");
    create<CanyonWorldCarver>("canyon");
//    create<UnderwaterCanyonWorldCarver>("underwater_canyon");
//    create<UnderwaterCaveWorldCarver>("underwater_cave");
}
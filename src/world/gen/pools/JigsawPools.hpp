#pragma once

#include <util/Registry.hpp>

struct JigsawPattern;
struct JigsawPools {
    static Registry<JigsawPattern> pools;

    static auto findByName(const std::string& name) -> JigsawPattern* {
        return pools.get(name).value_or(nullptr);
    }

    static void init();
};

struct PlainVillagePools {
    static void init();
};

struct SnowyVillagePools {
    static void init();
};

struct SavannaVillagePools {
    static void init();
};

struct DesertVillagePools {
    static void init();
};

struct TaigaVillagePools {
    static void init();
};

struct PillagerOutpostPools {
    static void init();
};

struct BastionRemnantsPieces {
    static void init();
};
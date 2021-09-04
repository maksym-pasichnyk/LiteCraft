#pragma once

#include <map>
#include <entity/EntityType.hpp>
#include <entity/EntityClassification.hpp>

struct MobSpawnInfo {
    struct Spawners {
        EntityType type;
        int weight;
        int minCount;
        int maxCount;
    };

    struct SpawnCosts {
        double maxSpawnCost;
        double entitySpawnCost;
    };

    float creatureSpawnProbability = 0.1f;
    std::map<EntityClassification, Spawners> spawners{};
    std::map<EntityType, SpawnCosts> spawnCosts{};
    bool playerSpawnFriendly = false;
};
#pragma once

enum class RuinedPortalLocation {
    STANDARD,
    DESERT,
    JUNGLE,
    SWAMP,
    MOUNTAIN,
    OCEAN,
    NETHER,
};

struct RuinedPortalConfig {
    RuinedPortalLocation location;
};
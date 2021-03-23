#pragma once

struct ConfiguredCarver;
struct ConfiguredCarvers {
    static ConfiguredCarver CAVE;
    static ConfiguredCarver CANYON;
    static ConfiguredCarver OCEAN_CAVE;
    static ConfiguredCarver NETHER_CAVE;

    static void configureCarvers();
};
#pragma once

struct Dimension {
    static const Dimension OVERWORLD;
    static const Dimension NETHER;
    static const Dimension THE_END;

    int id;
    int skyLight;
    void(*createBiomeSource)();
};
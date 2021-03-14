#pragma once

struct Biome;

//template<typename T>
//concept BiomeReader = requires(T self) {
//    requires requires(int x, int y, int z) {
//        {self.getNoiseBiome(x, y, z)} -> std::same_as<Biome*>;
//    };
//};

struct BiomeReader {
    virtual Biome* getNoiseBiome(int x, int y, int z) = 0;
};
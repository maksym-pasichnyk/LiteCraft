#pragma once

#include "src/world/gen/LazyAreaLayerContext.hpp"
#include "src/world/gen/area/IAreaFactory.hpp"
#include "Layer.hpp"

#include <cstdint>
#include <memory>
#include <functional>

class Layer;
class LazyAreaLayerContext;

struct LayerUtil {
    enum class Type {
        NONE,
        TAIGA,
        EXTREME_HILLS,
        JUNGLE,
        MESA,
        BADLANDS_PLATEAU,
        PLAINS,
        SAVANNA,
        ICY,
        BEACH,
        FOREST,
        OCEAN,
        DESERT,
        RIVER,
        SWAMP,
        MUSHROOM
    };

    [[gnu::pure]]
    static constexpr Type getType(int biomdId) noexcept {
        switch (biomdId) {
            case 16: return Type::BEACH;
            case 26: return Type::BEACH;
            case 2: return Type::DESERT;
            case 17: return Type::DESERT;
            case 130: return Type::DESERT;
            case 131: return Type::EXTREME_HILLS;
            case 162: return Type::EXTREME_HILLS;
            case 20: return Type::EXTREME_HILLS;
            case 3: return Type::EXTREME_HILLS;
            case 34: return Type::EXTREME_HILLS;
            case 27: return Type::FOREST;
            case 28: return Type::FOREST;
            case 29: return Type::FOREST;
            case 157: return Type::FOREST;
            case 132: return Type::FOREST;
            case 4: return Type::FOREST;
            case 155: return Type::FOREST;
            case 156: return Type::FOREST;
            case 18: return Type::FOREST;
            case 140: return Type::ICY;
            case 13: return Type::ICY;
            case 12: return Type::ICY;
            case 168: return Type::JUNGLE;
            case 169: return Type::JUNGLE;
            case 21: return Type::JUNGLE;
            case 23: return Type::JUNGLE;
            case 22: return Type::JUNGLE;
            case 149: return Type::JUNGLE;
            case 151: return Type::JUNGLE;
            case 37: return Type::MESA;
            case 165: return Type::MESA;
            case 167: return Type::MESA;
            case 166: return Type::MESA;
            case 39: return Type::BADLANDS_PLATEAU;
            case 38: return Type::BADLANDS_PLATEAU;
            case 14: return Type::MUSHROOM;
            case 15: return Type::MUSHROOM;
            case 25: return Type::NONE;
            case 46: return Type::OCEAN;
            case 49: return Type::OCEAN;
            case 50: return Type::OCEAN;
            case 48: return Type::OCEAN;
            case 24: return Type::OCEAN;
            case 47: return Type::OCEAN;
            case 10: return Type::OCEAN;
            case 45: return Type::OCEAN;
            case 0: return Type::OCEAN;
            case 44: return Type::OCEAN;
            case 1: return Type::PLAINS;
            case 129: return Type::PLAINS;
            case 11: return Type::RIVER;
            case 7: return Type::RIVER;
            case 35: return Type::SAVANNA;
            case 36: return Type::SAVANNA;
            case 163: return Type::SAVANNA;
            case 164: return Type::SAVANNA;
            case 6: return Type::SWAMP;
            case 134: return Type::SWAMP;
            case 160: return Type::TAIGA;
            case 161: return Type::TAIGA;
            case 32: return Type::TAIGA;
            case 33: return Type::TAIGA;
            case 30: return Type::TAIGA;
            case 31: return Type::TAIGA;
            case 158: return Type::TAIGA;
            case 5: return Type::TAIGA;
            case 19: return Type::TAIGA;
            case 133: return Type::TAIGA;
            default: return Type::NONE;
        }
    }

    static LayerUtil create(int64_t seed, int biome_scale, int32_t _4) {
        return {};
    }

    [[gnu::pure]]
    static constexpr bool isOcean(int biomeIn) noexcept {
        return biomeIn == 44 || biomeIn == 45 || biomeIn == 0 || biomeIn == 46 || biomeIn == 10 || biomeIn == 47 ||
               biomeIn == 48 || biomeIn == 24 || biomeIn == 49 || biomeIn == 50;
    }

    [[gnu::pure]]
    static constexpr bool isShallowOcean(int biomeIn) noexcept {
        return biomeIn == 44 || biomeIn == 45 || biomeIn == 0 || biomeIn == 46 || biomeIn == 10;
    }

    [[gnu::pure]]
    static constexpr bool areBiomesSimilar(int biome1, int biome2) noexcept {
        if (biome1 == biome2) return true;

        return getType(biome1) == getType(biome2);
    }

    static std::unique_ptr<Layer> createOverworldBiomes(int64_t seed, bool legacyBiomes, int biomeScale, int _4);

    static IAreaFactory<LazyArea> createOverworldBiomes(bool legacyBiomes, int biomeScale, int repeatCount, const std::function<std::unique_ptr<LazyAreaLayerContext>(int64_t)>& contextFactory);
};

#pragma once

#include <random>

struct Random {
	inline static constexpr auto RANDOM_MULTIPLIER = 0x5DEECE66DULL;
	inline static constexpr auto RANDOM_ADDEND = 0xBULL;
	inline static constexpr auto RANDOM_MASK = ((1ULL << 48u) - 1);
	inline static constexpr auto RANDOM_SCALE = 0x1.0p-53;

	static constexpr auto from(uint64_t seed) -> Random {
		Random rand;
		rand.setSeed(seed);
		return rand;
	}

	static constexpr auto seedSlimeChunk(int32_t x, int32_t z, int64_t baseSeed, int64_t modifier) -> Random {
		return from(baseSeed
		    + static_cast<int64_t>(x * x * 4987142)
		    + static_cast<int64_t>(x * 5947611)
		    + static_cast<int64_t>(z * z) * 4392871LL
		    + static_cast<int64_t>(z * 389711) ^ modifier);
	}

    constexpr auto nextInt(int32_t min, int32_t max) -> int32_t {
		return min + nextInt(max - min);
	}

    constexpr auto nextInt(int32_t bound) -> int32_t {
		int32_t r = next(31);
        int32_t m = bound - 1u;
		if ((bound & m) == 0) { // i.e., bound is a power of 2
			r = static_cast<int32_t>((bound * static_cast<uint64_t>(r)) >> 31u);
		} else {
			int32_t u = r;
			while (u - (r = u % bound) + m < 0) {
				u = next(31);
			}
		}
		return r;
	}

    constexpr auto next(int32_t bits) -> int32_t {
		seed = (seed * RANDOM_MULTIPLIER + RANDOM_ADDEND) & RANDOM_MASK;
		return static_cast<int32_t>(seed >> (48u - bits));
	}

    constexpr auto nextLong() -> int64_t {
        return (static_cast<int64_t>(next(32)) << 32) | next(32);
    }

    constexpr auto nextBoolean() -> bool {
        return next(1) != 0;
    }

    constexpr auto nextFloat() -> float {
        return static_cast<float>(next(24)) / 1.6777216E7F;
    }

    constexpr auto nextDouble() -> double {
    	return static_cast<double>(((static_cast<int64_t>(next(26)) << 27u)) | next(27)) * RANDOM_SCALE;
	}

    constexpr auto initialScramble(int64_t v) -> int64_t {
		return (v ^ RANDOM_MULTIPLIER) & RANDOM_MASK;
	}

    constexpr void skip(int32_t bits) {
        for (int32_t i = 0; i < bits; ++i) {
            next(1);
        }
    }

    constexpr void setSeed(uint64_t v) {
		seed = initialScramble(v);
	}

    constexpr auto setBaseChunkSeed(int32_t x, int32_t z) -> int64_t {
		auto i = static_cast<int64_t>(x) * 0x4F9939F508LL + static_cast<int64_t>(z) * 0x1ef1565bd5LL;
		setSeed(i);
		return i;
	}

    constexpr auto setDecorationSeed(int64_t baseSeed, int32_t x, int32_t z) -> int64_t {
		setSeed(baseSeed);
		const int64_t i = nextLong() | 1L;
        const int64_t j = nextLong() | 1L;
        const int64_t k = static_cast<int64_t>(x) * i + static_cast<int64_t>(z) * j ^ baseSeed;
		setSeed(k);
		return k;
	}

    constexpr auto setFeatureSeed(int64_t baseSeed, int32_t x, int32_t z) -> int64_t {
        const int64_t i = baseSeed + static_cast<int64_t>(x) + static_cast<int64_t>(10000 * z);
		setSeed(i);
		return i;
	}

    constexpr auto setLargeFeatureSeed(int64_t baseSeed, int32_t x, int32_t z) -> int64_t {
		setSeed(baseSeed);
        const int64_t i = nextLong();
        const int64_t j = nextLong();
        const int64_t k = static_cast<int64_t>(x) * i ^ static_cast<int64_t>(z) * j ^baseSeed;
		setSeed(k);
		return k;
	}

    constexpr auto setLargeFeatureSeedWithSalt(int64_t baseSeed, int32_t x, int32_t z, int32_t modifier) -> int64_t {
		const int64_t i = static_cast<int64_t>(x) * 0x4F9939F508LL + static_cast<int64_t>(z) * 0x1ef1565bd5LL + baseSeed + static_cast<int64_t>(modifier);
		setSeed(i);
		return i;
	}
private:
	uint64_t seed = 0;
};
#pragma once

#include <random>
#include <stdint.hpp>

struct Random {
	inline static constexpr auto RANDOM_MULTIPLIER = 0x5DEECE66DULL;
	inline static constexpr auto RANDOM_ADDEND = 0xBULL;
	inline static constexpr auto RANDOM_MASK = ((1ULL << 48u) - 1);
	inline static constexpr auto RANDOM_SCALE = 0x1.0p-53;

	static auto from(uint64 seed) -> Random {
		Random rand;
		rand.setSeed(seed);
		return rand;
	}

	static auto seedSlimeChunk(int32_t x, int32_t z, int64_t baseSeed, int64_t modifier) -> Random {
		return from(baseSeed + int64_t(x * x * 4987142) + int64_t(x * 5947611) + int64_t(z * z) * 4392871LL + int64_t(z * 389711) ^ modifier);
	}

	auto nextInt(int32_t min, int32_t max) -> int32_t {
		return min + nextInt(max - min);
	}

	auto nextInt(int bound) -> int32_t {
		int32_t r = next(31);
        int32_t m = bound - 1u;
		if ((bound & m) == 0) { // i.e., bound is a power of 2
			r = int32_t((bound * uint64(r)) >> 31u);
		} else {
			int32_t u = r;
			while (u - (r = u % bound) + m < 0) {
				u = next(31);
			}
		}
		return r;
	}

	auto next(int bits) -> int32_t {
		seed = (seed * RANDOM_MULTIPLIER + RANDOM_ADDEND) & RANDOM_MASK;
		return int32_t(seed >> (48u - bits));
	}

	auto nextLong() -> int64_t {
        return (int64_t(next(32)) << 32) | int64_t(next(32));
    }

    auto nextBoolean() -> bool {
        return next(1) != 0;
    }

    auto nextFloat() -> float {
        return float(next(24)) / 1.6777216E7F;
    }

	auto nextDouble() -> double {
    	return double(((int64_t(int32_t(next(26))) << 27u)) | int32_t(next(27))) * RANDOM_SCALE;
	}

	auto initialScramble(int64_t v) -> int64_t {
		return (v ^ RANDOM_MULTIPLIER) & RANDOM_MASK;
	}

	void setSeed(uint64 v) {
		seed = initialScramble(v);
	}

	auto setBaseChunkSeed(int32_t x, int32_t z) -> int64_t {
		auto i = int64_t(x) * 0x4F9939F508LL + int64_t(z) * 0x1ef1565bd5LL;
		setSeed(i);
		return i;
	}

	auto setDecorationSeed(int64_t baseSeed, int32_t x, int32_t z) -> int64_t {
		setSeed(baseSeed);
		int64_t i = nextLong() | 1L;
		int64_t j = nextLong() | 1L;
		int64_t k = int64_t(x) * i + int64_t(z) * j ^ baseSeed;
		setSeed(k);
		return k;
	}

	auto setFeatureSeed(int64_t baseSeed, int32_t x, int32_t z) -> int64_t {
		int64_t i = baseSeed + int64_t(x) + int64_t(10000 * z);
		setSeed(i);
		return i;
	}

	auto setLargeFeatureSeed(int64_t baseSeed, int32_t x, int32_t z) -> int64_t {
		setSeed(baseSeed);
		int64_t i = nextLong();
		int64_t j = nextLong();
		int64_t k = int64_t(x) * i ^ int64_t(z) * j ^baseSeed;
		setSeed(k);
		return k;
	}

	auto setLargeFeatureSeedWithSalt(int64_t baseSeed, int32_t x, int32_t z, int32_t modifier) -> int64_t {
		int64_t i = int64_t(x) * 0x4F9939F508LL + int64_t(z) * 0x1ef1565bd5LL + baseSeed + int64_t(modifier);
		setSeed(i);
		return i;
	}
private:
	uint64 seed = 0;
};
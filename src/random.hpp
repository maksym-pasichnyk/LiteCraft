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

	static auto seedSlimeChunk(int32 x, int32 z, long baseSeed, long modifier) -> Random {
		return from(baseSeed + int64(x * x * 4987142) + int64(x * 5947611) + int64(z * z) * 4392871LL + int64(z * 389711) ^ modifier);
	}

	auto nextInt(int32 min, int32 max) -> int32 {
		return min + nextInt(max - min);
	}

	auto nextInt(uint16 bound) -> int32 {
		int32 r = next(31);
		uint16 m = bound - 1u;
		if ((bound & m) == 0) {
			r = int32((bound * uint64(r)) >> 31u);
		} else {
			int32 u = r;
			while (u - (r = u % bound) + m < 0) {
				u = next(31);
			}
		}
		return r;
	}

	auto next(int bits) -> int32 {
		seed = (seed * RANDOM_MULTIPLIER + RANDOM_ADDEND) & RANDOM_MASK;
		return int32(seed >> (48u - bits));
	}

	auto nextLong() -> int64_t {
        return (int64(next(32)) << 32) | int64(next(32));
    }

    auto nextBoolean() -> bool {
        return next(1) != 0;
    }

    auto nextFloat() -> float {
        return float(next(24)) / 1.6777216E7F;
    }

	auto nextDouble() -> double {
    	return double(((int64(int32(next(26))) << 27u)) | int32(next(27))) * RANDOM_SCALE;
	}

	void advance4() {
		seed = (seed * 0x32EB772C5F11LLU + 0x2D3873C4CD04LLU) & RANDOM_MASK;
	}

	void advance6() {
		seed = (seed * 0x45D73749A7F9LLU + 0x17617168255ELLU) & RANDOM_MASK;
	}

	auto initialScramble(int64_t v) -> int64_t {
		return (v ^ RANDOM_MULTIPLIER) & RANDOM_MASK;
	}

	void setSeed(uint64 v) {
		seed = initialScramble(v);
	}

	auto setBaseChunkSeed(int32 x, int32 z) -> int64 {
		auto i = int64(x) * 0x4F9939F508LL + int64(z) * 0x1ef1565bd5LL;
		setSeed(i);
		return i;
	}

	auto setDecorationSeed(int64 baseSeed, int32 x, int32 z) -> int64 {
		setSeed(baseSeed);
		int64 i = nextLong() | 1L;
		int64 j = nextLong() | 1L;
		int64 k = int64(x) * i + int64(z) * j ^ baseSeed;
		setSeed(k);
		return k;
	}

	auto setFeatureSeed(int64 baseSeed, int32 x, int32 z) -> int64 {
		int64 i = baseSeed + int64(x) + int64(10000 * z);
		setSeed(i);
		return i;
	}

	auto setLargeFeatureSeed(int64 baseSeed, int32 x, int32 z) {
		setSeed(baseSeed);
		int64 i = nextLong();
		int64 j = nextLong();
		int64 k = int64(x) * i ^ int64(z) * j ^baseSeed;
		setSeed(k);
		return k;
	}

	auto setLargeFeatureSeedWithSalt(int64 baseSeed, int32 x, int32 z, int32 modifier) {
		int64 i = int64(x) * 0x4F9939F508LL + int64(z) * 0x1ef1565bd5LL + baseSeed + int64(modifier);
		setSeed(i);
		return i;
	}
private:
	uint64 seed = 0;
};
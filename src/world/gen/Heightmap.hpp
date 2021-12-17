#pragma once

#include <array>
#include <cstdint>
#include <block/BlockData.hpp>
#include <block/material/BlockMaterial.hpp>

enum class HeightmapType {
    WORLD_SURFACE_WG,
    WORLD_SURFACE,
    OCEAN_FLOOR_WG,
    OCEAN_FLOOR,
    MOTION_BLOCKING,
    MOTION_BLOCKING_NO_LEAVES
};

struct Heightmap {
    static constexpr uint64_t maxValue = 0x1FF;

    std::array<uint64_t, 37> data{};

    constexpr auto getAt(int i) const -> int {
        const auto s = (i % 7) * 9;
        return static_cast<int>((data[i / 7] >> s) & maxValue);
    }

    constexpr void setAt(int i, int v) {
        const auto s = (i % 7) * 9;
        data[i / 7] = data[i / 7] & ~(maxValue << s) | ((static_cast<uint64_t>(v) & maxValue) << s);
    }

    constexpr auto get(int x, int z) const -> int {
        return getAt(x | (z << 4));
    }

    constexpr void set(int x, int z, int v) {
        return setAt(x | (z << 4), v);
    }
};

struct HeightmapUtils {
    struct WorldSurface {
        static auto test(BlockData state) -> bool {
            return !state.isAir();
        }
    };
    struct OceanFloor {
        static auto test(BlockData state) -> bool {
            return state.getMaterial()->isBlocksMovement;
        }
    };
    struct MotionBlocking {
        static auto test(BlockData state) -> bool {
            return state.getMaterial()->isBlocksMovement
				|| state.getMaterial()->isLiquid;
        }
    };
    struct MotionBlockingNoLeaves {
        static auto test(BlockData state) -> bool {
            return MotionBlocking::test(state) && !state.in(BlockTags::LEAVES);
        }
    };

    static auto predicate(HeightmapType type) -> auto(*)(BlockData state) -> bool {
        const auto predicates = std::array{
			WorldSurface::test,
			WorldSurface::test,
			OceanFloor::test,
			OceanFloor::test,
			MotionBlocking::test,
			MotionBlockingNoLeaves::test,
        };
        return predicates.at(static_cast<size_t>(type));
    }

    static auto test(HeightmapType type, BlockData state) -> bool {
		return predicate(type)(state);
    }
};
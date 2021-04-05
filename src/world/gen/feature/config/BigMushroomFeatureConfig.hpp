#pragma once

struct BlockStateProvider;
struct BigMushroomFeatureConfig {
    BlockStateProvider* capProvider;
    BlockStateProvider* stemProvider;
    int foliageRadius;
};
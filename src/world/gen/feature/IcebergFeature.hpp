#pragma once

#include "Feature.hpp"

struct WorldWriter;
struct IcebergFeature : Feature {
    static int func_205178_b(int a, int b, int c);
    static int func_205183_a(Random& random, int a, int b, int c);
    static void func_205181_a(WorldGenRegion &region, Random& random, const BlockPos& pos, int e, int x, int y, int z, int a, int b, bool flag, int c, double d, bool flag2, BlockData state);
    static double func_205180_a(int x, int z, const BlockPos& pos, int a, int b, double c);
    static int func_205176_a(int a, int b, int c);
    static double func_205177_a(int a, int b, const BlockPos& pos, int c, Random& random);
    static void func_205175_a(const BlockPos& pos, WorldGenRegion &region, Random& random, int a, int b, bool p_205175_6_, bool p_205175_7_, BlockData p_205175_8_);
    static int func_205187_b(Random& random, int a, int b, int c);
    static void func_205186_a(WorldGenRegion& region, const BlockPos& pos, int a, int b, bool flag, int d);
    static bool isIce(Block* block);
    static bool isAirBellow(WorldReader& reader, const BlockPos& pos);
    static void func_205184_a(Random& random, WorldGenRegion& region, int a, int b, const BlockPos& pos, bool flag, int c, double d, int e);
    static void func_205174_a(int p_205174_1_, int yDiff, const BlockPos& p_205174_3_, WorldGenRegion& region, bool placeWater, double p_205174_6_, const BlockPos& p_205174_8_, int p_205174_9_, int p_205174_10_);
    static void removeSnowLayer(WorldGenRegion& region, const BlockPos& pos);

    bool generate(WorldGenRegion &region, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) override;
};
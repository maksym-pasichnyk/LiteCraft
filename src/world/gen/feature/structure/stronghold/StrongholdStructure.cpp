//#include "StrongholdStructure.hpp"
//#include "StrongholdPieces.hpp"
//#include "StrongholdStart.hpp"
//
//bool StrongholdStructure::canGenerate(ChunkGenerator &generator, BiomeProvider &biomes, int64_t seed, Random &random, int x, int z, Biome &biome, const ChunkPos &pos, const StructureConfig &config) {
////    random.setLargeFeatureSeed(seed, x, z);
////    return random.nextDouble() < std::get<StrongholdConfig>(config).probability;
//    return true;
//}
//
//StructureStart *StrongholdStructure::createStart(int x, int z, const BoundingBox &bounds, int refCount, int64_t seed) {
//    return new Start(this, x, z, bounds, refCount, seed);
//}
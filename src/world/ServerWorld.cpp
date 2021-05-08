#include "ServerWorld.hpp"

#include "biome/provider/SingleBiomeProvider.hpp"
#include "biome/provider/OverworldBiomeProvider.hpp"
#include "gen/NoiseChunkGenerator.hpp"
#include "ChunkManager.hpp"

ServerWorld::ServerWorld(CraftServer *server, int viewDistance) : server(server), viewDistance(viewDistance) {
    generator = std::make_unique<NoiseChunkGenerator>(seed, std::make_unique<OverworldBiomeProvider>(seed, false, false));
//        generator = std::make_unique<NoiseChunkGenerator>(seed, std::make_unique<SingleBiomeProvider>(Biomes::SWAMP));
    manager = std::make_unique<ChunkManager>(this, generator.get());
}

Biome *ServerWorld::getNoiseBiomeRaw(int x, int y, int z) {
    return generator->biomeProvider->getNoiseBiome(x, y, z);
}

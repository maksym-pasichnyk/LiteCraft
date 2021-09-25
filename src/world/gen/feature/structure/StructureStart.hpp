#pragma once

#include <util/Random.hpp>
#include "PieceGenerator.hpp"
#include "StructurePiece.hpp"
#include "config/StructureConfig.hpp"

#include <memory>
#include <vector>

struct Biome;
struct Structure;
struct StructurePiece;
struct ChunkGenerator;
struct TemplateManager;

struct StructureStart {
    std::vector<StructurePiece*> components;

    Structure* structure;
    int chunkx;
    int chunkz;
    BoundingBox bounds;
    int references;
    Random rand;

    StructureStart(std::vector<StructurePiece*> components, Structure* structure, int chunkx, int chunkz, BoundingBox bounds, int references, int64_t seed)
        : components(std::move(components)), structure(structure), chunkx(chunkx), chunkz(chunkz), bounds(bounds), references(references) {
        rand.setLargeFeatureSeed(seed, chunkx, chunkz);
    }

    virtual void generate(WorldGenRegion& region, StructureManager& structureManager, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos);

    virtual bool isValid() const {
        return !components.empty();
    }

    auto getBoundingBox() const -> BoundingBox {
        return bounds;
    }
};
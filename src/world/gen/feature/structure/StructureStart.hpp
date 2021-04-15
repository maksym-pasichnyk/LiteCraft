#pragma once

#include "StructurePiece.hpp"
#include "config/StructureConfig.hpp"
#include "../../../../util/Random.hpp"

#include <vector>
#include <memory>

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

    StructureStart(Structure* structure, int chunkx, int chunkz, BoundingBox bounds, int references, int64_t seed)
        : structure(structure), chunkx(chunkx), chunkz(chunkz), bounds(bounds), references(references) {
        rand.setLargeFeatureSeed(seed, chunkx, chunkz);
    }

    virtual void createComponents(/*DynamicRegistries p_230364_1_,*/ ChunkGenerator& generator, TemplateManager& templateManager, int chunkx, int chunkz, Biome& biome, const StructureConfig& config) = 0;
    virtual void generate(WorldGenRegion& region, StructureManager& structureManager, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos);

    virtual void recalculateStructureSize() {
        bounds = BoundingBox::getNewBoundingBox();

        for (auto& piece : components) {
            bounds.expandTo(piece->getBoundingBox());
        }
    }

    virtual bool isValid() const {
        return !components.empty();
    }

    void markAvailableHeight(int seaLevel, Random& random, int y) {
        const int i = seaLevel - y;
        int j = bounds.getYSize() + 1;
        if (j < i) {
            j += random.nextInt(i - j);
        }

        const int k = j - bounds.maxY;
        bounds.offset(0, k, 0);

        for (auto piece : components) {
            piece->offset(0, k, 0);
        }
    }

    BoundingBox getBoundingBox() const {
        return bounds;
    }
};
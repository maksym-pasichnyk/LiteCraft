#pragma once

#include "JigsawProjection.hpp"
#include "world/WorldGenRegion.hpp"
#include "world/gen/feature/structure/TemplateManager.hpp"
#include "world/gen/ChunkGenerator.hpp"
#include "util/Random.hpp"
#include "util/math/BoundingBox.hpp"

#include <memory>
#include <functional>
#include <Json.hpp>

struct ConfiguredFeature;
struct StructureProcessorList;

struct JigsawElement {
    using Factory = std::function<std::unique_ptr<JigsawElement>(JigsawProjection)>;

    JigsawProjection projection;

    explicit JigsawElement(JigsawProjection projection) : projection(projection) {}
    virtual ~JigsawElement() = default;

    virtual auto to_json() -> Json = 0;
    virtual auto getGroundLevelDelta() -> int {
        return 1;
    }

    static auto list(std::vector<Factory> factories) -> Factory;
    static auto single(std::string name) -> Factory;
    static auto single(std::string name, StructureProcessorList* processor) -> Factory;
    static auto feature(ConfiguredFeature* feature) -> Factory;
    static auto legacy(std::string name) -> Factory;
    static auto legacy(std::string name, StructureProcessorList* processor) -> Factory;
    static auto empty() -> Factory;

    static auto from_json(const Json& o) -> std::unique_ptr<JigsawElement>;

    virtual void place(WorldGenRegion &region, TemplateManager &manager, ChunkGenerator &generator, Random &random, const BoundingBox &box, const BlockPos &pos, const PlacementSettings& settings) {}
    virtual auto getJigsawBlocks(TemplateManager &manager, const BlockPos &pos, Rotation rotation, Random &random) -> std::vector<BlockInfo> {
        return {};
    }
    virtual auto getBoundingBox(TemplateManager& manager, const BlockPos& pos, Rotation rotation) -> BoundingBox {
        return BoundingBox::getNewBoundingBox();
    }
};

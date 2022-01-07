#pragma once

#include "JigsawElement.hpp"

struct SingleJigsawPiece : JigsawElement {
    std::string location;
    StructureProcessorList* processors;

    SingleJigsawPiece(std::string location, StructureProcessorList* processors, JigsawProjection projection)
        : JigsawElement(projection)
        , location(std::move(location))
        , processors(processors) {}

    auto to_json() -> Json override;
    static auto from_json(const Json& o) -> std::unique_ptr<JigsawElement>;

    void place(WorldGenRegion &region, TemplateManager &manager, ChunkGenerator &generator, Random &random, const BoundingBox &box, const BlockPos &pos, const PlacementSettings& settings) override;

    auto getJigsawBlocks(TemplateManager &manager, const BlockPos &pos, Rotation rotation, Random &random) -> std::vector<BlockInfo> override;
    auto getBoundingBox(TemplateManager &manager, const BlockPos &pos, Rotation rotation) -> BoundingBox override;
};
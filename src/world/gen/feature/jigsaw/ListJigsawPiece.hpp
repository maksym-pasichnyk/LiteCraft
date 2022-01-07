#pragma once

#include "JigsawElement.hpp"

struct ListJigsawPiece : JigsawElement {
    std::vector<std::unique_ptr<JigsawElement>> elements;

    ListJigsawPiece(std::vector<std::unique_ptr<JigsawElement>> pieces, JigsawProjection projection)
        : JigsawElement(projection)
        , elements(std::move(pieces)) {}

    auto to_json() -> Json override;
    static auto from_json(const Json& o) -> std::unique_ptr<JigsawElement>;

    void place(WorldGenRegion &region, TemplateManager &manager, ChunkGenerator &generator, Random &random, const BoundingBox &box, const BlockPos &pos, const PlacementSettings& settings) override {
        for (auto&& element : elements) {
            element->place(region, manager, generator, random, box, pos, settings);
        }
    }
    auto getJigsawBlocks(TemplateManager &manager, const BlockPos &pos, Rotation rotation, Random &random) -> std::vector<BlockInfo> override {
        return elements.at(0)->getJigsawBlocks(manager, pos, rotation, random);
    }

    auto getBoundingBox(TemplateManager &manager, const BlockPos &pos, Rotation rotation) -> BoundingBox override;
};
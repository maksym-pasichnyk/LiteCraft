#include "ShipwreckPiece.hpp"
#include <block/StairsBlock.hpp>
#include <world/WorldGenRegion.hpp>

bool ShipwreckPiece::addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) {
    for (auto&& info : structure_template->blocks) {
        if (info.state.isAir()) {
            continue;
        }

        const auto new_pos = structure_settings.calculateConnectedPosition(info.pos);
        const auto new_state = info.state.mirror(structure_settings.mirror).rotate(structure_settings.rotation);

        if (!bb.isVecInside(new_pos)) {
            continue;
        }
//
        region.setData(new_pos, new_state);
    }
    return true;
}
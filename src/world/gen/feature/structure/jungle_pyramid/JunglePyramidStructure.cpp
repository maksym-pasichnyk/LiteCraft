#include "JunglePyramidStructure.hpp"
#include "JunglePyramidPiece.hpp"
#include <configs.hpp>

void JunglePyramidStructure::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {
    auto random = Random::fromLargeFeatureSeed(context.seed, context.pos.x, context.pos.z);
    pieces.emplace(new JunglePyramidPiece(random, context.pos.getStartX(), context.pos.getStartZ()));
}

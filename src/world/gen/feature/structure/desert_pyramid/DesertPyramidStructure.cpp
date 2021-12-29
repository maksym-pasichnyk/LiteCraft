#include "DesertPyramidStructure.hpp"
#include "DesertPyramidPiece.hpp"

void DesertPyramidStructure::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {
    auto random = Random::fromLargeFeatureSeed(context.seed, context.pos.x, context.pos.z);
    pieces.emplace(new DesertPyramidPiece(random, context.pos.getStartX(), context.pos.getStartZ()));
}
#include "SwampHutStructure.hpp"
#include "SwampHutPiece.hpp"

void SwampHutStructure::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {
    auto random = Random::fromLargeFeatureSeed(context.seed, context.pos.x, context.pos.z);
    pieces.emplace(new SwampHutPiece(random, context.pos.getStartX(), context.pos.getStartZ()));
}

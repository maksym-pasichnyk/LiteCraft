#include "SwampHutStructure.hpp"
#include "SwampHutPiece.hpp"
#include <configs.hpp>

void SwampHutStructure::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {
    auto random = Random::fromLargeFeatureSeed(context.seed, context.pos.x, context.pos.z);
    pieces.emplace(new SwampHutPiece(random, context.pos.getStartX(), context.pos.getStartZ()));
}

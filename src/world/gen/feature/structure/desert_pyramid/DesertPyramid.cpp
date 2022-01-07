#include "DesertPyramid.hpp"
#include "DesertPyramidPiece.hpp"

auto DesertPyramid::create() -> std::unique_ptr<Structure> {
    return std::make_unique<Structure>(Structure{
        .generatePieces = createComponents
    });
}

void DesertPyramid::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {
    auto random = Random::fromLargeFeatureSeed(context.seed, context.pos.x, context.pos.z);
    pieces.emplace(new DesertPyramidPiece(random, context.pos.getStartX(), context.pos.getStartZ()));
}
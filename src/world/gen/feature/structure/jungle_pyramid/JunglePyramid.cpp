#include "JunglePyramid.hpp"
#include "JunglePyramidPiece.hpp"

auto JunglePyramid::create() -> std::unique_ptr<Structure> {
    return std::make_unique<Structure>(Structure{
        .generatePieces = createComponents
    });
}

void JunglePyramid::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {
    auto random = Random::fromLargeFeatureSeed(context.seed, context.pos.x, context.pos.z);
    pieces.emplace(new JunglePyramidPiece(random, context.pos.getStartX(), context.pos.getStartZ()));
}
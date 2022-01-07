#include "Igloo.hpp"

auto Igloo::create() -> std::unique_ptr<Structure> {
	return std::make_unique<Structure>(Structure{
        .generatePieces = createComponents
	});
}

void Igloo::createComponents(StructurePieces &pieces, StructureGenerateContext &context, const StructureConfig &config) {}

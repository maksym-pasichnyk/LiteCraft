#include "BastionRemnantStructure.hpp"
#include "world/gen/feature/structure/village/VillageStructure.hpp"

void BastionRemnantStructure::createComponents(StructurePieces &pieces, StructureGenerateContext &context, const StructureConfig &config) {
    VillageStructure::createComponents(pieces, context, config);
}

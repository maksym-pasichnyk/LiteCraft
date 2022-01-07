#include "PillagerOutpostStructure.hpp"
#include "world/gen/feature/structure/village/VillageStructure.hpp"

void PillagerOutpostStructure::createComponents(StructurePieces &pieces, StructureGenerateContext &context, const StructureConfig &config) {
    VillageStructure::createComponents(pieces, context, config);
}

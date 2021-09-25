#include "StructurePieces.hpp"
#include "StructureGenerateContext.hpp"

struct Biome;
struct Structure;
struct ChunkGenerator;
struct TemplateManager;

using PieceGenerator = void(*)(StructurePieces&, StructureGenerateContext& context, const StructureConfig& config);
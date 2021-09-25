#include "config/StructureConfig.hpp"
#include "StructurePieces.hpp"

struct Biome;
struct Structure;
struct ChunkGenerator;
struct TemplateManager;

using PieceGenerator = void(*)(StructurePieces&, ChunkGenerator&, TemplateManager&, int, int, Biome&, const StructureConfig&, int64_t);
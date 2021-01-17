//module;

#include "block_reader.hpp"
#include "tile.hpp"

#include <glm/glm.hpp>
#include <optional>

//export module raytrace;

struct RayTraceContext {
	glm::vec3 position;
	glm::vec3 direction;
};

struct RayTraceResult {
	glm::ivec3 pos;
	Tile* tile{nullptr};
};

auto rayTraceBlocks(IBlockReader auto& blocks, const RayTraceContext& context) -> std::optional<RayTraceResult> {
	auto rayPos = context.position;
	auto rayDir = context.direction;

	glm::ivec3 mapPos = glm::ivec3(glm::floor(rayPos));
	glm::vec3 deltaDist = glm::abs(glm::vec3(glm::length(rayDir)) / rayDir);

	glm::ivec3 rayStep = glm::ivec3(glm::sign(rayDir));

	glm::vec3 sideDist = (glm::sign(rayDir) * (glm::vec3(mapPos) - rayPos) + (glm::sign(rayDir) * 0.5f) + 0.5f) * deltaDist;

	int i = 10;
	while (i-- > 0) {
		auto mask = glm::lessThanEqual(sideDist, glm::min(glm::vec3(sideDist.y, sideDist.z, sideDist.x), glm::vec3(sideDist.z, sideDist.x, sideDist.y)));

		sideDist += glm::vec3(mask) * deltaDist;
		mapPos += glm::ivec3(glm::vec3(mask)) * rayStep;

		// todo: shape

		auto tile = blocks.getTile(mapPos.x, mapPos.y, mapPos.z);
		if (tile != Tile::air) {
			return RayTraceResult{
				.pos = mapPos,
				.tile = tile
			};
		}
	}

	return std::nullopt;
}

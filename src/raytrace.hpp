//module;

#include "block/Block.hpp"
#include "block/BlockReader.hpp"
#include "block/material/BlockMaterial.hpp"
#include "block/material/Materials.hpp"

#include <glm/glm.hpp>
#include <tl/optional.hpp>

//export module raytrace;

struct RayTraceContext {
	glm::vec3 position;
	glm::vec3 direction;
	bool ignoreLiquid;
};

struct RayTraceResult {
	glm::ivec3 pos;
	glm::ivec3 dir;
	BlockData state;
};

template <typename IBlockReader>
auto rayTraceBlocks(IBlockReader /*auto*/& blocks, const RayTraceContext& context) -> tl::optional<RayTraceResult> {
    const auto rayPos = context.position;
	const auto rayDir = context.direction;

	auto pos = glm::ivec3(glm::floor(rayPos));
	const auto deltaDist = glm::abs(glm::vec3(glm::length(rayDir)) / rayDir);
	const auto rayStep = glm::ivec3(glm::sign(rayDir));

	auto sideDist = (glm::sign(rayDir) * (glm::vec3(pos) - rayPos) + (glm::sign(rayDir) * 0.5f) + 0.5f) * deltaDist;

	int i = 10;
	while (i-- > 0) {
		const auto mask = glm::lessThanEqual(sideDist, glm::min(glm::vec3(sideDist.y, sideDist.z, sideDist.x), glm::vec3(sideDist.z, sideDist.x, sideDist.y)));
        const auto dir = glm::ivec3(mask) * rayStep;

		sideDist += glm::vec3(mask) * deltaDist;
        pos += dir;

		// todo: shape

		const auto state = blocks.getData(pos);
		if (!state.isAir() && !(context.ignoreLiquid && state.getMaterial()->isLiquid)) {
			return RayTraceResult{
				.pos = pos,
				.dir = -dir,
				.state = state
			};
		}
	}

	return tl::nullopt;
}

#include "SingleJigsawPiece.hpp"
#include <world/gen/feature/processor/ProcessorLists.hpp>
#include <configs.hpp>

auto SingleJigsawPiece::to_json() -> Json {
	return {
        {"type", "single"},
        {"location", location},
        {"projection", projection},
        {"processors", ProcessorLists::processors.name(processors).value()}
    };
}

#include "SingleJigsawPiece.hpp"
#include <world/gen/feature/processor/ProcessorLists.hpp>

auto SingleJigsawPiece::to_json() -> Json {
	return {
        {"type", "single"},
        {"location", location},
        {"projection", projection},
        {"processors", ProcessorLists::processors.name(processors).value()}
    };
}

auto SingleJigsawPiece::from_json(const Json &o) -> std::unique_ptr<JigsawPiece> {
    auto processors = ProcessorLists::processors.get(o.at("processors").as_string().value()).value();
    return std::make_unique<SingleJigsawPiece>(o.at("location").as_string().value(), processors, o.at("projection"));
}

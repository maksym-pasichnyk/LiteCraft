#include "JigsawElement.hpp"
#include "ListJigsawPiece.hpp"
#include "EmptyJigsawPiece.hpp"
#include "SingleJigsawPiece.hpp"
#include "FeatureJigsawPiece.hpp"
#include "LegacySingleJigsawPiece.hpp"
#include <world/gen/feature/processor/ProcessorLists.hpp>

auto JigsawElement::list(std::vector<Factory> factories) -> Factory {
    return [factories = std::move(factories)](JigsawProjection placement) -> std::unique_ptr<JigsawElement> {
        auto pieces = cpp_iter(factories).map([placement](auto&& factory) { return factory(placement); }).collect();
        return std::make_unique<ListJigsawPiece>(std::move(pieces), placement);
    };
}

auto JigsawElement::single(std::string name) -> JigsawElement::Factory {
    return [name = std::move(name)](JigsawProjection placement) -> std::unique_ptr<JigsawElement> {
        return std::make_unique<SingleJigsawPiece>(name, ProcessorLists::EMPTY, placement);
    };
}

auto JigsawElement::single(std::string name, StructureProcessorList *processors) -> JigsawElement::Factory {
    return [name = std::move(name), processors](JigsawProjection placement) -> std::unique_ptr<JigsawElement> {
        return std::make_unique<SingleJigsawPiece>(name, processors, placement);
    };
}

auto JigsawElement::feature(ConfiguredFeature *feature) -> Factory {
    return [feature](JigsawProjection placement) -> std::unique_ptr<JigsawElement> {
        return std::make_unique<FeatureJigsawPiece>(feature, placement);
    };
}

auto JigsawElement::legacy(std::string name) -> JigsawElement::Factory {
    return [name = std::move(name)](JigsawProjection placement) -> std::unique_ptr<JigsawElement> {
        return std::make_unique<LegacySingleJigsawPiece>(name, ProcessorLists::EMPTY, placement);
    };
}

auto JigsawElement::legacy(std::string name, StructureProcessorList *processors) -> JigsawElement::Factory {
    return [name = std::move(name), processors](JigsawProjection placement) -> std::unique_ptr<JigsawElement> {
        return std::make_unique<LegacySingleJigsawPiece>(name, processors, placement);
    };
}

auto JigsawElement::empty() -> JigsawElement::Factory {
    return [](JigsawProjection) -> std::unique_ptr<JigsawElement> {
        return std::make_unique<EmptyJigsawPiece>();
    };
}

auto JigsawElement::from_json(const Json& o) -> std::unique_ptr<JigsawElement> {
    using namespace std::string_literals;

    static auto table = std::map{
        std::pair{"empty"s, &EmptyJigsawPiece::from_json},
        std::pair{"feature"s, &FeatureJigsawPiece::from_json},
        std::pair{"list"s, &ListJigsawPiece::from_json},
        std::pair{"single"s, &SingleJigsawPiece::from_json}
    };
    return table.at(o.at("type").as_string().value())(o);
}

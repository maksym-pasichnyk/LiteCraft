#include "JigsawPiece.hpp"
#include "ListJigsawPiece.hpp"
#include "EmptyJigsawPiece.hpp"
#include "SingleJigsawPiece.hpp"
#include "FeatureJigsawPiece.hpp"
#include "LegacySingleJigsawPiece.hpp"
#include <world/gen/feature/processor/ProcessorLists.hpp>

auto JigsawPiece::list(std::vector<Factory> factories) -> Factory {
    return [factories = std::move(factories)](JigsawProjection placement) -> std::unique_ptr<JigsawPiece> {
        auto pieces = factories | ranges::views::transform([placement](auto&& factory) { return factory(placement); });
        return std::make_unique<ListJigsawPiece>(pieces | ranges::to_vector, placement);
    };
}

auto JigsawPiece::single(std::string name) -> JigsawPiece::Factory {
    return [name = std::move(name)](JigsawProjection placement) -> std::unique_ptr<JigsawPiece> {
        return std::make_unique<SingleJigsawPiece>(name, ProcessorLists::EMPTY, placement);
    };
}

auto JigsawPiece::single(std::string name, StructureProcessorList *processors) -> JigsawPiece::Factory {
    return [name = std::move(name), processors](JigsawProjection placement) -> std::unique_ptr<JigsawPiece> {
        return std::make_unique<SingleJigsawPiece>(name, processors, placement);
    };
}

auto JigsawPiece::feature(ConfiguredFeature *feature) -> Factory {
    return [feature](JigsawProjection placement) -> std::unique_ptr<JigsawPiece> {
        return std::make_unique<FeatureJigsawPiece>(feature, placement);
    };
}

auto JigsawPiece::legacy(std::string name) -> JigsawPiece::Factory {
    return [name = std::move(name)](JigsawProjection placement) -> std::unique_ptr<JigsawPiece> {
        return std::make_unique<LegacySingleJigsawPiece>(name, ProcessorLists::EMPTY, placement);
    };
}

auto JigsawPiece::legacy(std::string name, StructureProcessorList *processors) -> JigsawPiece::Factory {
    return [name = std::move(name), processors](JigsawProjection placement) -> std::unique_ptr<JigsawPiece> {
        return std::make_unique<LegacySingleJigsawPiece>(name, processors, placement);
    };
}

auto JigsawPiece::empty() -> JigsawPiece::Factory {
    return [](JigsawProjection) -> std::unique_ptr<JigsawPiece> {
        return std::make_unique<EmptyJigsawPiece>();
    };
}

auto JigsawPiece::from_json(const Json& o) -> std::unique_ptr<JigsawPiece> {
    using namespace std::string_literals;

    static auto table = std::map<std::string, std::unique_ptr<JigsawPiece>(*)(const Json&)> {
        {"empty"s, &EmptyJigsawPiece::from_json},
        {"feature"s, &FeatureJigsawPiece::from_json},
        {"list"s, &ListJigsawPiece::from_json},
        {"single"s, &SingleJigsawPiece::from_json}
    };
    return table.at(o.at("type").as_string().value())(o);
}

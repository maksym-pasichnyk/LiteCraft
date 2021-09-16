#include "JigsawPiece.hpp"
#include "ListJigsawPiece.hpp"
#include "EmptyJigsawPiece.hpp"
#include "SingleJigsawPiece.hpp"
#include "FeatureJigsawPiece.hpp"
#include "LegacySingleJigsawPiece.hpp"
#include <world/gen/feature/processor/ProcessorLists.hpp>

#include <range/v3/all.hpp>

auto JigsawPiece::list(std::vector<Factory> factories) -> Factory {
    return [factories = std::move(factories)](JigsawProjection placement) -> JigsawPiece * {
        auto pieces = factories | ranges::views::transform([placement](auto&& factory) { return factory(placement); });
        return new ListJigsawPiece(pieces | ranges::to_vector, placement);
    };
}

auto JigsawPiece::single(std::string name) -> JigsawPiece::Factory {
    return [name = std::move(name)](JigsawProjection placement) -> JigsawPiece * {
        return new SingleJigsawPiece(name, ProcessorLists::EMPTY, placement);
    };
}

auto JigsawPiece::single(std::string name, StructureProcessorList *processors) -> JigsawPiece::Factory {
    return [name = std::move(name), processors](JigsawProjection placement) -> JigsawPiece * {
        return new SingleJigsawPiece(name, processors, placement);
    };
}

auto JigsawPiece::feature(ConfiguredFeature *feature) -> Factory {
    return [feature](JigsawProjection placement) -> JigsawPiece * {
        return new FeatureJigsawPiece(feature, placement);
    };
}

auto JigsawPiece::legacy(std::string name) -> JigsawPiece::Factory {
    return [name = std::move(name)](JigsawProjection placement) -> JigsawPiece * {
        return new LegacySingleJigsawPiece(name, ProcessorLists::EMPTY, placement);
    };
}

auto JigsawPiece::legacy(std::string name, StructureProcessorList *processors) -> JigsawPiece::Factory {
    return [name = std::move(name), processors](JigsawProjection placement) -> JigsawPiece * {
        return new LegacySingleJigsawPiece(name, processors, placement);
    };
}

auto JigsawPiece::empty() -> JigsawPiece::Factory {
    return [](JigsawProjection) -> JigsawPiece * {
        return new EmptyJigsawPiece();
    };
}
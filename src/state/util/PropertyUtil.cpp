#include "PropertyUtil.hpp"

#include <map>
#include <string>
#include <Json.hpp>
#include <util/Codec.hpp>
#include <tl/optional.hpp>
#include <spdlog/fmt/fmt.h>

template <typename T> struct IntoString {
    using Value = T;
    using Result = tl::optional<std::string>;
    
    static auto into(const T& s) -> Result;
};
template <typename T> struct FromString {
    using Self = std::string;
    using Result = tl::optional<T>;
    
    static auto from(const Self& s) -> Result;
};

template <>
auto FromString<bool>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, bool> {
        {"true", true},
        {"false", false},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<int>::from(const Self& s) -> Result {
    return std::stoi(s);
}

template <>
auto FromString<Half>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, Half> {
        {"top", Half::TOP},
        {"bottom", Half::BOTTOM},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<BedPart>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, BedPart> {
        {"head", BedPart::HEAD},
        {"foot", BedPart::FOOT},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<SlabType>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, SlabType> {
        {"top", SlabType::TOP},
        {"bottom", SlabType::BOTTOM},
        {"double", SlabType::DOUBLE},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<RailShape>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, RailShape> {
        {"north_south", RailShape::NORTH_SOUTH},
        {"east_west", RailShape::EAST_WEST},
        {"ascending_east", RailShape::ASCENDING_EAST},
        {"ascending_west", RailShape::ASCENDING_WEST},
        {"ascending_north", RailShape::ASCENDING_NORTH},
        {"ascending_south", RailShape::ASCENDING_SOUTH},
        {"south_east", RailShape::SOUTH_EAST},
        {"south_west", RailShape::SOUTH_WEST},
        {"north_west", RailShape::NORTH_WEST},
        {"north_east", RailShape::NORTH_EAST},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<ChestType>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, ChestType> {
        {"single", ChestType::SINGLE},
        {"left", ChestType::LEFT},
        {"right", ChestType::RIGHT},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<Direction>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, Direction> {
        {"north", Direction::NORTH},
        {"south", Direction::SOUTH},
        {"east", Direction::EAST},
        {"west", Direction::WEST},
        {"up", Direction::UP},
        {"down", Direction::DOWN},
        {"bottom", Direction::DOWN}
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<PistonType>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, PistonType> {
        {"normal", PistonType::DEFAULT},
        {"sticky", PistonType::STICKY},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<AttachFace>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, AttachFace> {
        {"floor", AttachFace::FLOOR},
        {"wall", AttachFace::WALL},
        {"ceiling", AttachFace::CEILING}
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<WallHeight>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, WallHeight> {
        {"none", WallHeight::NONE },
        {"low", WallHeight::LOW },
        {"tall", WallHeight::TALL }
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<StairsShape>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, StairsShape> {
        {"straight", StairsShape::STRAIGHT},
        {"inner_left", StairsShape::INNER_LEFT},
        {"inner_right", StairsShape::INNER_RIGHT},
        {"outer_left", StairsShape::OUTER_LEFT},
        {"outer_right", StairsShape::OUTER_RIGHT},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<RedstoneSide>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, RedstoneSide> {
        {"up", RedstoneSide::UP},
        {"side", RedstoneSide::SIDE},
        {"none", RedstoneSide::NONE},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<BambooLeaves>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, BambooLeaves> {
        {"none", BambooLeaves::NONE},
        {"small", BambooLeaves::SMALL},
        {"large", BambooLeaves::LARGE},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<DoorHingeSide>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, DoorHingeSide> {
        {"left", DoorHingeSide::LEFT},
        {"right", DoorHingeSide::RIGHT},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<StructureMode>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, StructureMode> {
        {"save", StructureMode::SAVE},
        {"load", StructureMode::LOAD},
        {"corner", StructureMode::CORNER},
        {"data", StructureMode::DATA},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<DirectionAxis>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, DirectionAxis> {
        {"x", DirectionAxis::X},
        {"y", DirectionAxis::Y},
        {"z", DirectionAxis::Z}
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<ComparatorMode>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, ComparatorMode> {
        {"compare", ComparatorMode::COMPARE},
        {"subtract", ComparatorMode::SUBTRACT},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<BellAttachment>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, BellAttachment> {
        {"floor", BellAttachment::FLOOR},
        {"ceiling", BellAttachment::CEILING},
        {"single_wall", BellAttachment::SINGLE_WALL},
        {"double_wall", BellAttachment::DOUBLE_WALL}
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<DoubleBlockHalf>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, DoubleBlockHalf> {
        {"upper", DoubleBlockHalf::UPPER},
        {"lower", DoubleBlockHalf::LOWER},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<JigsawOrientation>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, JigsawOrientation> {
        {"down_east", JigsawOrientation::DOWN_EAST},
        {"down_north", JigsawOrientation::DOWN_NORTH},
        {"down_south", JigsawOrientation::DOWN_SOUTH},
        {"down_west", JigsawOrientation::DOWN_WEST},
        {"up_east", JigsawOrientation::UP_EAST},
        {"up_north", JigsawOrientation::UP_NORTH},
        {"up_south", JigsawOrientation::UP_SOUTH},
        {"up_west", JigsawOrientation::UP_WEST},
        {"west_up", JigsawOrientation::WEST_UP},
        {"east_up", JigsawOrientation::EAST_UP},
        {"north_up", JigsawOrientation::NORTH_UP},
        {"south_up", JigsawOrientation::SOUTH_UP},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto FromString<NoteBlockInstrument>::from(const Self& s) -> Result {
    static auto table = std::map<std::string, NoteBlockInstrument> {
        {"harp", NoteBlockInstrument::HARP},
        {"basedrum", NoteBlockInstrument::BASEDRUM},
        {"snare", NoteBlockInstrument::SNARE},
        {"hat", NoteBlockInstrument::HAT},
        {"bass", NoteBlockInstrument::BASS},
        {"flute", NoteBlockInstrument::FLUTE},
        {"bell", NoteBlockInstrument::BELL},
        {"guitar", NoteBlockInstrument::GUITAR},
        {"chime", NoteBlockInstrument::CHIME},
        {"xylophone", NoteBlockInstrument::XYLOPHONE},
        {"iron_xylophone", NoteBlockInstrument::IRON_XYLOPHONE},
        {"cow_bell", NoteBlockInstrument::COW_BELL},
        {"didgeridoo", NoteBlockInstrument::DIDGERIDOO},
        {"bit", NoteBlockInstrument::BIT},
        {"banjo", NoteBlockInstrument::BANJO},
        {"pling", NoteBlockInstrument::PLING},
    };

    if (auto it = table.find(s); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<bool>::into(const Value& v) -> Result {
    static auto table = std::map<bool, std::string>{
        {true, "true"},
        {false, "false"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<int>::into(const Value& v) -> Result {
    return fmt::format("{}", v);
}

template <>
auto IntoString<Half>::into(const Value& v) -> Result {
    static auto table = std::map<Half, std::string> {
        {Half::TOP, "top"},
        {Half::BOTTOM, "bottom"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<BedPart>::into(const Value& v) -> Result {
    static auto table = std::map<BedPart, std::string> {
        {BedPart::HEAD, "head"},
        {BedPart::FOOT, "foot"},
    };

    if (auto it = table.find(v); it != table.end()) {
     return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<SlabType>::into(const Value& v) -> Result {
    static auto table = std::map<SlabType, std::string> {
        {SlabType::TOP, "top"},
        {SlabType::BOTTOM, "bottom"},
        {SlabType::DOUBLE, "double"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<RailShape>::into(const Value& v) -> Result {
    static auto table = std::map<RailShape, std::string> {
        {RailShape::NORTH_SOUTH, "north_south"},
        {RailShape::EAST_WEST, "east_west"},
        {RailShape::ASCENDING_EAST, "ascending_east"},
        {RailShape::ASCENDING_WEST, "ascending_west"},
        {RailShape::ASCENDING_NORTH, "ascending_north"},
        {RailShape::ASCENDING_SOUTH, "ascending_south"},
        {RailShape::SOUTH_EAST, "south_east"},
        {RailShape::SOUTH_WEST, "south_west"},
        {RailShape::NORTH_WEST, "north_west"},
        {RailShape::NORTH_EAST, "north_east"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<ChestType>::into(const Value& v) -> Result {
    static auto table = std::map<ChestType, std::string> {
        {ChestType::SINGLE, "single"},
        {ChestType::LEFT, "left"},
        {ChestType::RIGHT, "right"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<Direction>::into(const Value& v) -> Result {
    static auto table = std::map<Direction, std::string> {
        {Direction::NORTH, "north"},
        {Direction::SOUTH, "south"},
        {Direction::EAST, "east"},
        {Direction::WEST, "west"},
        {Direction::UP, "up"},
        {Direction::DOWN, "down"}
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<PistonType>::into(const Value& v) -> Result {
    static auto table = std::map<PistonType, std::string> {
        {PistonType::DEFAULT, "normal"},
        {PistonType::STICKY, "sticky"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<AttachFace>::into(const Value& v) -> Result {
    static auto table = std::map<AttachFace, std::string> {
        {AttachFace::FLOOR, "floor"},
        {AttachFace::WALL, "wall"},
        {AttachFace::CEILING, "ceiling"}
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<WallHeight>::into(const Value& v) -> Result {
    static auto table = std::map<WallHeight, std::string> {
        {WallHeight::NONE , "none"},
        {WallHeight::LOW , "low"},
        {WallHeight::TALL , "tall"}
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<StairsShape>::into(const Value& v) -> Result {
    static auto table = std::map<StairsShape, std::string> {
        {StairsShape::STRAIGHT, "straight"},
        {StairsShape::INNER_LEFT, "inner_left"},
        {StairsShape::INNER_RIGHT, "inner_right"},
        {StairsShape::OUTER_LEFT, "outer_left"},
        {StairsShape::OUTER_RIGHT, "outer_right"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<RedstoneSide>::into(const Value& v) -> Result {
    static auto table = std::map<RedstoneSide, std::string> {
        {RedstoneSide::UP, "up"},
        {RedstoneSide::SIDE, "side"},
        {RedstoneSide::NONE, "none"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<BambooLeaves>::into(const Value& v) -> Result {
    static auto table = std::map<BambooLeaves, std::string> {
        {BambooLeaves::NONE, "none"},
        {BambooLeaves::SMALL, "small"},
        {BambooLeaves::LARGE, "large"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<DoorHingeSide>::into(const Value& v) -> Result {
    static auto table = std::map<DoorHingeSide, std::string> {
        {DoorHingeSide::LEFT, "left"},
        {DoorHingeSide::RIGHT, "right"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<StructureMode>::into(const Value& v) -> Result {
    static auto table = std::map<StructureMode, std::string> {
        {StructureMode::SAVE, "save"},
        {StructureMode::LOAD, "load"},
        {StructureMode::CORNER, "corner"},
        {StructureMode::DATA, "data"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<DirectionAxis>::into(const Value& v) -> Result {
    static auto table = std::map<DirectionAxis, std::string> {
        {DirectionAxis::X, "x"},
        {DirectionAxis::Y, "y"},
        {DirectionAxis::Z, "z"}
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<ComparatorMode>::into(const Value& v) -> Result {
    static auto table = std::map<ComparatorMode, std::string> {
        {ComparatorMode::COMPARE, "compare"},
        {ComparatorMode::SUBTRACT, "subtract"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<BellAttachment>::into(const Value& v) -> Result {
    static auto table = std::map<BellAttachment, std::string> {
        {BellAttachment::FLOOR, "floor"},
        {BellAttachment::CEILING, "ceiling"},
        {BellAttachment::SINGLE_WALL, "single_wall"},
        {BellAttachment::DOUBLE_WALL, "double_wall"}
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<DoubleBlockHalf>::into(const Value& v) -> Result {
    static auto table = std::map<DoubleBlockHalf, std::string> {
        {DoubleBlockHalf::UPPER, "upper"},
        {DoubleBlockHalf::LOWER, "lower"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<JigsawOrientation>::into(const Value& v) -> Result {
    static auto table = std::map<JigsawOrientation, std::string> {
        {JigsawOrientation::DOWN_EAST, "down_east"},
        {JigsawOrientation::DOWN_NORTH, "down_north"},
        {JigsawOrientation::DOWN_SOUTH, "down_south"},
        {JigsawOrientation::DOWN_WEST, "down_west"},
        {JigsawOrientation::UP_EAST, "up_east"},
        {JigsawOrientation::UP_NORTH, "up_north"},
        {JigsawOrientation::UP_SOUTH, "up_south"},
        {JigsawOrientation::UP_WEST, "up_west"},
        {JigsawOrientation::WEST_UP, "west_up"},
        {JigsawOrientation::EAST_UP, "east_up"},
        {JigsawOrientation::NORTH_UP, "north_up"},
        {JigsawOrientation::SOUTH_UP, "south_up"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template <>
auto IntoString<NoteBlockInstrument>::into(const Value& v) -> Result {
    static auto table = std::map<NoteBlockInstrument, std::string> {
        {NoteBlockInstrument::HARP, "harp"},
        {NoteBlockInstrument::BASEDRUM, "basedrum"},
        {NoteBlockInstrument::SNARE, "snare"},
        {NoteBlockInstrument::HAT, "hat"},
        {NoteBlockInstrument::BASS, "bass"},
        {NoteBlockInstrument::FLUTE, "flute"},
        {NoteBlockInstrument::BELL, "bell"},
        {NoteBlockInstrument::GUITAR, "guitar"},
        {NoteBlockInstrument::CHIME, "chime"},
        {NoteBlockInstrument::XYLOPHONE, "xylophone"},
        {NoteBlockInstrument::IRON_XYLOPHONE, "iron_xylophone"},
        {NoteBlockInstrument::COW_BELL, "cow_bell"},
        {NoteBlockInstrument::DIDGERIDOO, "didgeridoo"},
        {NoteBlockInstrument::BIT, "bit"},
        {NoteBlockInstrument::BANJO, "banjo"},
        {NoteBlockInstrument::PLING, "pling"},
    };

    if (auto it = table.find(v); it != table.end()) {
        return it->second;
    }
    return tl::nullopt;
}

template<>
auto Json::Into<Half>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<BedPart>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<SlabType>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<RailShape>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<ChestType>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<Direction>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<PistonType>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<AttachFace>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<WallHeight>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<StairsShape>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<RedstoneSide>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<BambooLeaves>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<DoorHingeSide>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<StructureMode>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<DirectionAxis>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<ComparatorMode>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<BellAttachment>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<DoubleBlockHalf>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<JigsawOrientation>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}
template<>
auto Json::Into<NoteBlockInstrument>::into(const Json& o) -> Result {
    return o.as_string().and_then(FromString<Value>::from);
}

template<>
auto Json::From<Half>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<BedPart>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<SlabType>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<RailShape>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<ChestType>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<Direction>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<PistonType>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<AttachFace>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<WallHeight>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<StairsShape>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<RedstoneSide>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<BambooLeaves>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<DoorHingeSide>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<StructureMode>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<DirectionAxis>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<ComparatorMode>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<BellAttachment>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<DoubleBlockHalf>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<JigsawOrientation>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}
template<>
auto Json::From<NoteBlockInstrument>::from(const Value& value) -> Self {
    return IntoString<Value>::into(value).value();
}

template<>
auto Json::From<PropertyValue>::from(const Value& value) -> Self {
    return match(value, []<typename T>(const T& item) -> Self {
        return Self(item);
    });
}

namespace {
    struct PropertyInfo {
        std::string name;
        Codec<PropertyValue> codec;
        std::vector<PropertyValue> values;
    };

    template<Property property>
    constexpr auto codec = Codec<PropertyValue>{
        .parse = [](const Nbt::Tag& tag) -> tl::optional<PropertyValue> {
            using T = typename TypeFrom<property>::type;
            return FromString<T>::from(std::get<Nbt::String>(tag.m_storage));
        },
        .write = [](const PropertyValue& value) -> tl::optional<Nbt::Tag> {
            const auto str = match(value, []<typename T>(const T& self) -> tl::optional<std::string> {
                return IntoString<T>::into(self);
            });
            if (str.has_value()) {
                return std::move(*str);
            }
            return tl::nullopt;
        }
    };

    const auto properties = std::array{
        // BooleanProperty
        PropertyInfo{"attached", codec<Property::ATTACHED>, {true, false}},
        PropertyInfo{"bottom", codec<Property::BOTTOM>, {true, false}},
        PropertyInfo{"conditional", codec<Property::CONDITIONAL>, {true, false}},
        PropertyInfo{"disarmed", codec<Property::DISARMED>, {true, false}},
        PropertyInfo{"drag", codec<Property::DRAG>, {true, false}},
        PropertyInfo{"enabled", codec<Property::ENABLED>, {true, false}},
        PropertyInfo{"extended", codec<Property::EXTENDED>, {true, false}},
        PropertyInfo{"eye", codec<Property::EYE>, {true, false}},
        PropertyInfo{"falling", codec<Property::FALLING>, {true, false}},
        PropertyInfo{"hanging", codec<Property::HANGING>, {true, false}},
        PropertyInfo{"has_bottle_0", codec<Property::HAS_BOTTLE_0>, {true, false}},
        PropertyInfo{"has_bottle_1", codec<Property::HAS_BOTTLE_1>, {true, false}},
        PropertyInfo{"has_bottle_2", codec<Property::HAS_BOTTLE_2>, {true, false}},
        PropertyInfo{"has_record", codec<Property::HAS_RECORD>, {true, false}},
        PropertyInfo{"has_book", codec<Property::HAS_BOOK>, {true, false}},
        PropertyInfo{"inverted", codec<Property::INVERTED>, {true, false}},
        PropertyInfo{"in_wall", codec<Property::IN_WALL>, {true, false}},
        PropertyInfo{"lit", codec<Property::LIT>, {true, false}},
        PropertyInfo{"locked", codec<Property::LOCKED>, {true, false}},
        PropertyInfo{"occupied", codec<Property::OCCUPIED>, {true, false}},
        PropertyInfo{"open", codec<Property::OPEN>, {true, false}},
        PropertyInfo{"persistent", codec<Property::PERSISTENT>, {true, false}},
        PropertyInfo{"powered", codec<Property::POWERED>, {true, false}},
        PropertyInfo{"short", codec<Property::SHORT>, {true, false}},
        PropertyInfo{"fire", codec<Property::SIGNAL_FIRE>, {true, false}},
        PropertyInfo{"snowy", codec<Property::SNOWY>, {true, false}},
        PropertyInfo{"triggered", codec<Property::TRIGGERED>, {true, false}},
        PropertyInfo{"unstable", codec<Property::UNSTABLE>, {true, false}},
        PropertyInfo{"waterlogged", codec<Property::WATERLOGGED>, {true, false}},
        PropertyInfo{"vine_end", codec<Property::VINE_END>, {true, false}},
        PropertyInfo{"up", codec<Property::UP>, {true, false}},
        PropertyInfo{"down", codec<Property::DOWN>, {true, false}},
        PropertyInfo{"north", codec<Property::NORTH>, {true, false}},
        PropertyInfo{"east", codec<Property::EAST>, {true, false}},
        PropertyInfo{"south", codec<Property::SOUTH>, {true, false}},
        PropertyInfo{"west", codec<Property::WEST>, {true, false}},
        // DirectionProperty
        PropertyInfo{"facing", codec<Property::FACING>, {Direction::DOWN, Direction::UP, Direction::NORTH, Direction::SOUTH, Direction::WEST, Direction::EAST}},
        PropertyInfo{"facing", codec<Property::FACING_EXCEPT_UP>, {Direction::DOWN, Direction::NORTH, Direction::SOUTH, Direction::WEST, Direction::EAST}},
        PropertyInfo{"facing", codec<Property::HORIZONTAL_FACING>, {Direction::NORTH, Direction::SOUTH, Direction::WEST, Direction::EAST}},
        // EnumProperty
        PropertyInfo{"axis", codec<Property::HORIZONTAL_AXIS>, {DirectionAxis::X, DirectionAxis::Z}},
        PropertyInfo{"axis", codec<Property::AXIS>, {DirectionAxis::X, DirectionAxis::Y, DirectionAxis::Z}},
        PropertyInfo{"orientation", codec<Property::ORIENTATION>, {JigsawOrientation::DOWN_EAST, JigsawOrientation::DOWN_NORTH, JigsawOrientation::DOWN_SOUTH, JigsawOrientation::DOWN_WEST, JigsawOrientation::UP_EAST, JigsawOrientation::UP_NORTH, JigsawOrientation::UP_SOUTH, JigsawOrientation::UP_WEST, JigsawOrientation::WEST_UP, JigsawOrientation::EAST_UP, JigsawOrientation::NORTH_UP, JigsawOrientation::SOUTH_UP}},
        PropertyInfo{"face", codec<Property::FACE>, {AttachFace::FLOOR, AttachFace::WALL, AttachFace::CEILING}},
        PropertyInfo{"attachment", codec<Property::BELL_ATTACHMENT>, {BellAttachment::FLOOR, BellAttachment::CEILING, BellAttachment::SINGLE_WALL, BellAttachment::DOUBLE_WALL}},
        PropertyInfo{"east", codec<Property::WALL_HEIGHT_EAST>, {WallHeight::NONE, WallHeight::LOW, WallHeight::TALL}},
        PropertyInfo{"north", codec<Property::WALL_HEIGHT_NORTH>, {WallHeight::NONE, WallHeight::LOW, WallHeight::TALL}},
        PropertyInfo{"south", codec<Property::WALL_HEIGHT_SOUTH>, {WallHeight::NONE, WallHeight::LOW, WallHeight::TALL}},
        PropertyInfo{"west", codec<Property::WALL_HEIGHT_WEST>, {WallHeight::NONE, WallHeight::LOW, WallHeight::TALL}},
        PropertyInfo{"east", codec<Property::REDSTONE_EAST>, {RedstoneSide::UP, RedstoneSide::SIDE, RedstoneSide::NONE}},
        PropertyInfo{"north", codec<Property::REDSTONE_NORTH>, {RedstoneSide::UP, RedstoneSide::SIDE, RedstoneSide::NONE}},
        PropertyInfo{"south", codec<Property::REDSTONE_SOUTH>, {RedstoneSide::UP, RedstoneSide::SIDE, RedstoneSide::NONE}},
        PropertyInfo{"west", codec<Property::REDSTONE_WEST>, {RedstoneSide::UP, RedstoneSide::SIDE, RedstoneSide::NONE}},
        PropertyInfo{"half", codec<Property::DOUBLE_BLOCK_HALF>, {DoubleBlockHalf::UPPER, DoubleBlockHalf::LOWER}},
        PropertyInfo{"half", codec<Property::HALF>, {Half::TOP, Half::BOTTOM}},
        PropertyInfo{"shape", codec<Property::RAIL_SHAPE>, {RailShape::NORTH_SOUTH, RailShape::EAST_WEST, RailShape::ASCENDING_EAST, RailShape::ASCENDING_WEST, RailShape::ASCENDING_NORTH, RailShape::ASCENDING_SOUTH, RailShape::SOUTH_EAST, RailShape::SOUTH_WEST, RailShape::NORTH_WEST, RailShape::NORTH_EAST}},
        PropertyInfo{"shape", codec<Property::RAIL_SHAPE_STRAIGHT>, {RailShape::NORTH_SOUTH, RailShape::EAST_WEST, RailShape::ASCENDING_WEST, RailShape::ASCENDING_NORTH, RailShape::ASCENDING_SOUTH}},
        PropertyInfo{"part", codec<Property::BED_PART>, {BedPart::HEAD, BedPart::FOOT}},
        PropertyInfo{"type", codec<Property::CHEST_TYPE>, {ChestType::SINGLE, ChestType::LEFT, ChestType::RIGHT}},
        PropertyInfo{"mode", codec<Property::COMPARATOR_MODE>, {ComparatorMode::COMPARE, ComparatorMode::SUBTRACT}},
        PropertyInfo{"hinge", codec<Property::DOOR_HINGE>, {DoorHingeSide::LEFT, DoorHingeSide::RIGHT}},
        PropertyInfo{"instrument", codec<Property::NOTE_BLOCK_INSTRUMENT>, {NoteBlockInstrument::HARP, NoteBlockInstrument::BASEDRUM, NoteBlockInstrument::SNARE, NoteBlockInstrument::HAT, NoteBlockInstrument::BASS, NoteBlockInstrument::FLUTE, NoteBlockInstrument::BELL, NoteBlockInstrument::GUITAR, NoteBlockInstrument::CHIME, NoteBlockInstrument::XYLOPHONE, NoteBlockInstrument::IRON_XYLOPHONE, NoteBlockInstrument::COW_BELL, NoteBlockInstrument::DIDGERIDOO, NoteBlockInstrument::BIT, NoteBlockInstrument::BANJO, NoteBlockInstrument::PLING}},
        PropertyInfo{"type", codec<Property::PISTON_TYPE>, {PistonType::DEFAULT, PistonType::STICKY}},
        PropertyInfo{"type", codec<Property::SLAB_TYPE>, {SlabType::TOP, SlabType::BOTTOM, SlabType::DOUBLE}},
        PropertyInfo{"shape", codec<Property::STAIRS_SHAPE>, {StairsShape::STRAIGHT, StairsShape::INNER_LEFT, StairsShape::INNER_RIGHT, StairsShape::OUTER_LEFT, StairsShape::OUTER_RIGHT}},
        PropertyInfo{"mode", codec<Property::STRUCTURE_BLOCK_MODE>, {StructureMode::SAVE, StructureMode::LOAD, StructureMode::CORNER, StructureMode::DATA}},
        PropertyInfo{"leaves", codec<Property::BAMBOO_LEAVES>, {BambooLeaves::NONE, BambooLeaves::SMALL, BambooLeaves::LARGE}},
        // IntegerProperty
        PropertyInfo{"age", codec<Property::AGE_0_1>, {0, 1}},
        PropertyInfo{"age", codec<Property::AGE_0_2>, {0, 1, 2}},
        PropertyInfo{"age", codec<Property::AGE_0_3>, {0, 1, 2, 3}},
        PropertyInfo{"age", codec<Property::AGE_0_5>, {0, 1, 2, 3, 4, 5}},
        PropertyInfo{"age", codec<Property::AGE_0_7>, {0, 1, 2, 3, 4, 5, 6, 7}},
        PropertyInfo{"age", codec<Property::AGE_0_15>, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}},
        PropertyInfo{"age", codec<Property::AGE_0_25>, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}},
        PropertyInfo{"bites", codec<Property::BITES_0_6>, {0, 1, 2, 3, 4, 5, 6}},
        PropertyInfo{"delay", codec<Property::DELAY_1_4>, {1, 2, 3, 4}},
        PropertyInfo{"distance", codec<Property::DISTANCE_1_7>, {1, 2, 3, 4, 5, 6, 7}},
        PropertyInfo{"eggs", codec<Property::EGGS_1_4>, {1, 2, 3, 4}},
        PropertyInfo{"hatch", codec<Property::HATCH_0_2>, {0, 1, 2}},
        PropertyInfo{"layers", codec<Property::LAYERS_1_8>, {1, 2, 3, 4, 5, 6, 7, 8}},
        PropertyInfo{"level", codec<Property::LEVEL_0_3>, {0, 1, 2, 3}},
        PropertyInfo{"level", codec<Property::LEVEL_0_8>, {0, 1, 2, 3, 4, 5, 6, 7, 8}},
        PropertyInfo{"level", codec<Property::LEVEL_1_8>, {1, 2, 3, 4, 5, 6, 7, 8}},
        PropertyInfo{"honey_level", codec<Property::HONEY_LEVEL>, {0, 1, 2, 3, 4, 5}},
        PropertyInfo{"level", codec<Property::LEVEL_0_15>, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}},
        PropertyInfo{"moisture", codec<Property::MOISTURE_0_7>, {0, 1, 2, 3, 4, 5, 6, 7}},
        PropertyInfo{"note", codec<Property::NOTE_0_24>, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}},
        PropertyInfo{"pickles", codec<Property::PICKLES_1_4>, {1, 2, 3, 4}},
        PropertyInfo{"power", codec<Property::POWER_0_15>, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}},
        PropertyInfo{"stage", codec<Property::STAGE_0_1>, {0, 1}},
        PropertyInfo{"distance", codec<Property::DISTANCE_0_7>, {0, 1, 2, 3, 4, 5, 6, 7}},
        PropertyInfo{"charges", codec<Property::CHARGES>, {0, 1, 2, 3, 4}},
        PropertyInfo{"rotation", codec<Property::ROTATION_0_15>, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}},
    };
}

auto PropertyUtil::name(Property property) -> std::string {
    return properties.at(static_cast<size_t>(property)).name;
}

auto PropertyUtil::values(Property property) -> std::span<const PropertyValue> {
    return properties.at(static_cast<size_t>(property)).values;
}

auto PropertyUtil::parse(Property property, const Nbt::Tag& tag) -> tl::optional<PropertyValue> {
    return properties.at(static_cast<size_t>(property)).codec.parse(tag);
}

auto PropertyUtil::write(Property property, const PropertyValue & value) -> tl::optional<Nbt::Tag> {
    return properties.at(static_cast<size_t>(property)).codec.write(value);
}

auto PropertyUtil::string(const PropertyValue& value) -> tl::optional<std::string> {
    return match(value, []<typename T>(const T& self) -> tl::optional<std::string> {
        return IntoString<T>::into(self);
    });
}
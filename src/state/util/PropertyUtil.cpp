#include "PropertyUtil.hpp"

#include <map>
#include <string>
#include <optional>
#include <util/Codec.hpp>

template <typename T> struct ToString {
    static auto from(const T& s) -> std::optional<std::string> = delete;
};
template <typename T> struct FromString {
    static auto from(const std::string& s) -> std::optional<T> = delete;
};

template <> struct FromString<bool> {
    static auto from(const std::string& s) -> std::optional<bool> {
        static auto table = std::map<std::string, bool> {
            {"true", true},
            {"false", false},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<int> {
    static auto from(const std::string& s) -> std::optional<bool> {
        return std::stoi(s);
    }
};

template <> struct FromString<Half> {
    static auto from(const std::string& s) -> std::optional<Half> {
        static auto table = std::map<std::string, Half> {
            {"top", Half::TOP},
            {"bottom", Half::BOTTOM},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<BedPart> {
    static auto from(const std::string& s) -> std::optional<BedPart> {
        static auto table = std::map<std::string, BedPart> {
            {"head", BedPart::HEAD},
            {"foot", BedPart::FOOT},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<SlabType> {
    static auto from(const std::string& s) -> std::optional<SlabType> {
        static auto table = std::map<std::string, SlabType> {
            {"top", SlabType::TOP},
            {"bottom", SlabType::BOTTOM},
            {"double", SlabType::DOUBLE},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<RailShape> {
    static auto from(const std::string& s) -> std::optional<RailShape> {
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
        return std::nullopt;
    }
};

template <> struct FromString<ChestType> {
    static auto from(const std::string& s) -> std::optional<ChestType> {
        static auto table = std::map<std::string, ChestType> {
            {"single", ChestType::SINGLE},
            {"left", ChestType::LEFT},
            {"right", ChestType::RIGHT},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<Direction> {
    static auto from(const std::string& s) -> std::optional<Direction> {
        static auto table = std::map<std::string, Direction> {
            {"north", Direction::NORTH},
            {"south", Direction::SOUTH},
            {"east", Direction::EAST},
            {"west", Direction::WEST},
            {"up", Direction::UP},
            {"down", Direction::DOWN}
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<PistonType> {
    static auto from(const std::string& s) -> std::optional<PistonType> {
        static auto table = std::map<std::string, PistonType> {
            {"default", PistonType::DEFAULT},
            {"sticky", PistonType::STICKY},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<AttachFace> {
    static auto from(const std::string& s) -> std::optional<AttachFace> {
        static auto table = std::map<std::string, AttachFace> {
            {"floor", AttachFace::FLOOR},
            {"wall", AttachFace::WALL},
            {"ceiling", AttachFace::CEILING}
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<WallHeight> {
    static auto from(const std::string& s) -> std::optional<WallHeight> {
        static auto table = std::map<std::string, WallHeight> {
            {"none", WallHeight::NONE },
            {"low", WallHeight::LOW },
            {"tall", WallHeight::TALL }
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<StairsShape> {
    static auto from(const std::string& s) -> std::optional<StairsShape> {
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
        return std::nullopt;
    }
};

template <> struct FromString<RedstoneSide> {
    static auto from(const std::string& s) -> std::optional<RedstoneSide> {
        static auto table = std::map<std::string, RedstoneSide> {
            {"up", RedstoneSide::UP},
            {"side", RedstoneSide::SIDE},
            {"none", RedstoneSide::NONE},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<BambooLeaves> {
    static auto from(const std::string& s) -> std::optional<BambooLeaves> {
        static auto table = std::map<std::string, BambooLeaves> {
            {"none", BambooLeaves::NONE},
            {"small", BambooLeaves::SMALL},
            {"large", BambooLeaves::LARGE},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<DoorHingeSide> {
    static auto from(const std::string& s) -> std::optional<DoorHingeSide> {
        static auto table = std::map<std::string, DoorHingeSide> {
            {"left", DoorHingeSide::LEFT},
            {"right", DoorHingeSide::RIGHT},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<StructureMode> {
    static auto from(const std::string& s) -> std::optional<StructureMode> {
        static auto table = std::map<std::string, StructureMode> {
            {"save", StructureMode::SAVE},
            {"load", StructureMode::LOAD},
            {"corner", StructureMode::CORNER},
            {"data", StructureMode::DATA},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<DirectionAxis> {
    static auto from(const std::string& s) -> std::optional<DirectionAxis> {
        static auto table = std::map<std::string, DirectionAxis> {
            {"x", DirectionAxis::X},
            {"y", DirectionAxis::Y},
            {"z", DirectionAxis::Z}
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<ComparatorMode> {
    static auto from(const std::string& s) -> std::optional<ComparatorMode> {
        static auto table = std::map<std::string, ComparatorMode> {
            {"compare", ComparatorMode::COMPARE},
            {"subtract", ComparatorMode::SUBTRACT},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<BellAttachment> {
    static auto from(const std::string& s) -> std::optional<BellAttachment> {
        static auto table = std::map<std::string, BellAttachment> {
            {"floor", BellAttachment::FLOOR},
            {"ceiling", BellAttachment::CEILING},
            {"single_wall", BellAttachment::SINGLE_WALL},
            {"double_wall", BellAttachment::DOUBLE_WALL}
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<DoubleBlockHalf> {
    static auto from(const std::string& s) -> std::optional<DoubleBlockHalf> {
        static auto table = std::map<std::string, DoubleBlockHalf> {
            {"upper", DoubleBlockHalf::UPPER},
            {"lower", DoubleBlockHalf::LOWER},
        };

        if (auto it = table.find(s); it != table.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

template <> struct FromString<JigsawOrientation> {
    static auto from(const std::string& s) -> std::optional<JigsawOrientation> {
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
        return std::nullopt;
    }
};

template <> struct FromString<NoteBlockInstrument> {
    static auto from(const std::string& s) -> std::optional<NoteBlockInstrument> {
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
        return std::nullopt;
    }
};

namespace {
    struct PropertyInfo {
        std::string name;
        Codec<PropertyValue> codec;
    };

    template<Property property>
    constexpr auto codec = Codec<PropertyValue>{
        .parse = [](const Nbt::Tag& tag) -> std::optional<PropertyValue> {
            using T = typename TypeFrom<property>::type;
            return FromString<T>::from(std::get<Nbt::String>(tag.m_storage));
        },
        .write = [](const PropertyValue & value) -> std::optional<Nbt::Tag> {
            return std::nullopt;
        }
    };

    const auto behaviour = std::array{
        // BooleanProperty
        PropertyInfo{"attached", codec<Property::ATTACHED>},
        PropertyInfo{"bottom", codec<Property::BOTTOM>},
        PropertyInfo{"conditional", codec<Property::CONDITIONAL>},
        PropertyInfo{"disarmed", codec<Property::DISARMED>},
        PropertyInfo{"drag", codec<Property::DRAG>},
        PropertyInfo{"enabled", codec<Property::ENABLED>},
        PropertyInfo{"extended", codec<Property::EXTENDED>},
        PropertyInfo{"eye", codec<Property::EYE>},
        PropertyInfo{"falling", codec<Property::FALLING>},
        PropertyInfo{"hanging", codec<Property::HANGING>},
        PropertyInfo{"has_bottle_0", codec<Property::HAS_BOTTLE_0>},
        PropertyInfo{"has_bottle_1", codec<Property::HAS_BOTTLE_1>},
        PropertyInfo{"has_bottle_2", codec<Property::HAS_BOTTLE_2>},
        PropertyInfo{"has_record", codec<Property::HAS_RECORD>},
        PropertyInfo{"has_book", codec<Property::HAS_BOOK>},
        PropertyInfo{"inverted", codec<Property::INVERTED>},
        PropertyInfo{"in_wall", codec<Property::IN_WALL>},
        PropertyInfo{"lit", codec<Property::LIT>},
        PropertyInfo{"locked", codec<Property::LOCKED>},
        PropertyInfo{"occupied", codec<Property::OCCUPIED>},
        PropertyInfo{"open", codec<Property::OPEN>},
        PropertyInfo{"persistent", codec<Property::PERSISTENT>},
        PropertyInfo{"powered", codec<Property::POWERED>},
        PropertyInfo{"short", codec<Property::SHORT>},
        PropertyInfo{"fire", codec<Property::SIGNAL_FIRE>},
        PropertyInfo{"snowy", codec<Property::SNOWY>},
        PropertyInfo{"triggered", codec<Property::TRIGGERED>},
        PropertyInfo{"unstable", codec<Property::UNSTABLE>},
        PropertyInfo{"waterlogged", codec<Property::WATERLOGGED>},
        PropertyInfo{"vine_end", codec<Property::VINE_END>},
        PropertyInfo{"up", codec<Property::UP>},
        PropertyInfo{"down", codec<Property::DOWN>},
        PropertyInfo{"north", codec<Property::NORTH>},
        PropertyInfo{"east", codec<Property::EAST>},
        PropertyInfo{"south", codec<Property::SOUTH>},
        PropertyInfo{"west", codec<Property::WEST>},
        // DirectionProperty
        PropertyInfo{"facing", codec<Property::FACING>},
        PropertyInfo{"facing", codec<Property::FACING_EXCEPT_UP>},
        PropertyInfo{"facing", codec<Property::HORIZONTAL_FACING>},
        // EnumProperty
        PropertyInfo{"axis", codec<Property::HORIZONTAL_AXIS>},
        PropertyInfo{"axis", codec<Property::AXIS>},
        PropertyInfo{"orientation", codec<Property::ORIENTATION>},
        PropertyInfo{"face", codec<Property::FACE>},
        PropertyInfo{"attachment", codec<Property::BELL_ATTACHMENT>},
        PropertyInfo{"east", codec<Property::WALL_HEIGHT_EAST>},
        PropertyInfo{"north", codec<Property::WALL_HEIGHT_NORTH>},
        PropertyInfo{"south", codec<Property::WALL_HEIGHT_SOUTH>},
        PropertyInfo{"west", codec<Property::WALL_HEIGHT_WEST>},
        PropertyInfo{"east", codec<Property::REDSTONE_EAST>},
        PropertyInfo{"north", codec<Property::REDSTONE_NORTH>},
        PropertyInfo{"south", codec<Property::REDSTONE_SOUTH>},
        PropertyInfo{"west", codec<Property::REDSTONE_WEST>},
        PropertyInfo{"half", codec<Property::DOUBLE_BLOCK_HALF>},
        PropertyInfo{"half", codec<Property::HALF>},
        PropertyInfo{"shape", codec<Property::RAIL_SHAPE>},
        PropertyInfo{"shape", codec<Property::RAIL_SHAPE_STRAIGHT>},
        PropertyInfo{"part", codec<Property::BED_PART>},
        PropertyInfo{"type", codec<Property::CHEST_TYPE>},
        PropertyInfo{"mode", codec<Property::COMPARATOR_MODE>},
        PropertyInfo{"hinge", codec<Property::DOOR_HINGE>},
        PropertyInfo{"instrument", codec<Property::NOTE_BLOCK_INSTRUMENT>},
        PropertyInfo{"type", codec<Property::PISTON_TYPE>},
        PropertyInfo{"type", codec<Property::SLAB_TYPE>},
        PropertyInfo{"shape", codec<Property::STAIRS_SHAPE>},
        PropertyInfo{"mode", codec<Property::STRUCTURE_BLOCK_MODE>},
        PropertyInfo{"leaves", codec<Property::BAMBOO_LEAVES>},
        // IntegerProperty
        PropertyInfo{"age", codec<Property::AGE_0_1>},
        PropertyInfo{"age", codec<Property::AGE_0_2>},
        PropertyInfo{"age", codec<Property::AGE_0_3>},
        PropertyInfo{"age", codec<Property::AGE_0_5>},
        PropertyInfo{"age", codec<Property::AGE_0_7>},
        PropertyInfo{"age", codec<Property::AGE_0_15>},
        PropertyInfo{"age", codec<Property::AGE_0_25>},
        PropertyInfo{"bites", codec<Property::BITES_0_6>},
        PropertyInfo{"delay", codec<Property::DELAY_1_4>},
        PropertyInfo{"distance", codec<Property::DISTANCE_1_7>},
        PropertyInfo{"eggs", codec<Property::EGGS_1_4>},
        PropertyInfo{"hatch", codec<Property::HATCH_0_2>},
        PropertyInfo{"layers", codec<Property::LAYERS_1_8>},
        PropertyInfo{"level", codec<Property::LEVEL_0_3>},
        PropertyInfo{"level", codec<Property::LEVEL_0_8>},
        PropertyInfo{"level", codec<Property::LEVEL_1_8>},
        PropertyInfo{"level", codec<Property::HONEY_LEVEL>},
        PropertyInfo{"level", codec<Property::LEVEL_0_15>},
        PropertyInfo{"moisture", codec<Property::MOISTURE_0_7>},
        PropertyInfo{"note", codec<Property::NOTE_0_24>},
        PropertyInfo{"pickles", codec<Property::PICKLES_1_4>},
        PropertyInfo{"power", codec<Property::POWER_0_15>},
        PropertyInfo{"stage", codec<Property::STAGE_0_1>},
        PropertyInfo{"distance", codec<Property::DISTANCE_0_7>},
        PropertyInfo{"charges", codec<Property::CHARGES>},
        PropertyInfo{"rotation", codec<Property::ROTATION_0_15>},
    };
}

auto PropertyUtil::name(Property property) -> std::optional<std::string> {
    return behaviour[static_cast<size_t>(property)].name;
}

auto PropertyUtil::parse(Property property, const Nbt::Tag& tag) -> std::optional<PropertyValue> {
    return behaviour[static_cast<size_t>(property)].codec.parse(tag);
}

auto PropertyUtil::write(Property property, const PropertyValue & value) -> std::optional<Nbt::Tag> {
    return behaviour[static_cast<size_t>(property)].codec.write(value);
}
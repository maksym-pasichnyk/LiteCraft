#pragma once

#include <nbt/nbt.hpp>
#include <state/Property.hpp>
#include <state/BlockStateProperties.hpp>

template <Property> struct TypeFrom;

template <> struct TypeFrom<Property::ATTACHED> {
    using type = bool;
};
template <> struct TypeFrom<Property::BOTTOM> {
    using type = bool;
};
template <> struct TypeFrom<Property::CONDITIONAL> {
    using type = bool;
};
template <> struct TypeFrom<Property::DISARMED> {
    using type = bool;
};
template <> struct TypeFrom<Property::DRAG> {
    using type = bool;
};
template <> struct TypeFrom<Property::ENABLED> {
    using type = bool;
};
template <> struct TypeFrom<Property::EXTENDED> {
    using type = bool;
};
template <> struct TypeFrom<Property::EYE> {
    using type = bool;
};
template <> struct TypeFrom<Property::FALLING> {
    using type = bool;
};
template <> struct TypeFrom<Property::HANGING> {
    using type = bool;
};
template <> struct TypeFrom<Property::HAS_BOTTLE_0> {
    using type = bool;
};
template <> struct TypeFrom<Property::HAS_BOTTLE_1> {
    using type = bool;
};
template <> struct TypeFrom<Property::HAS_BOTTLE_2> {
    using type = bool;
};
template <> struct TypeFrom<Property::HAS_RECORD> {
    using type = bool;
};
template <> struct TypeFrom<Property::HAS_BOOK> {
    using type = bool;
};
template <> struct TypeFrom<Property::INVERTED> {
    using type = bool;
};
template <> struct TypeFrom<Property::IN_WALL> {
    using type = bool;
};
template <> struct TypeFrom<Property::LIT> {
    using type = bool;
};
template <> struct TypeFrom<Property::LOCKED> {
    using type = bool;
};
template <> struct TypeFrom<Property::OCCUPIED> {
    using type = bool;
};
template <> struct TypeFrom<Property::OPEN> {
    using type = bool;
};
template <> struct TypeFrom<Property::PERSISTENT> {
    using type = bool;
};
template <> struct TypeFrom<Property::POWERED> {
    using type = bool;
};
template <> struct TypeFrom<Property::SHORT> {
    using type = bool;
};
template <> struct TypeFrom<Property::SIGNAL_FIRE> {
    using type = bool;
};
template <> struct TypeFrom<Property::SNOWY> {
    using type = bool;
};
template <> struct TypeFrom<Property::TRIGGERED> {
    using type = bool;
};
template <> struct TypeFrom<Property::UNSTABLE> {
    using type = bool;
};
template <> struct TypeFrom<Property::WATERLOGGED> {
    using type = bool;
};
template <> struct TypeFrom<Property::VINE_END> {
    using type = bool;
};
template <> struct TypeFrom<Property::UP> {
    using type = bool;
};
template <> struct TypeFrom<Property::DOWN> {
    using type = bool;
};
template <> struct TypeFrom<Property::NORTH> {
    using type = bool;
};
template <> struct TypeFrom<Property::EAST> {
    using type = bool;
};
template <> struct TypeFrom<Property::SOUTH> {
    using type = bool;
};
template <> struct TypeFrom<Property::WEST> {
    using type = bool;
};
template <> struct TypeFrom<Property::FACING> {
    using type = Direction;
};
template <> struct TypeFrom<Property::FACING_EXCEPT_UP> {
    using type = Direction;
};
template <> struct TypeFrom<Property::HORIZONTAL_FACING> {
    using type = Direction;
};
template <> struct TypeFrom<Property::HORIZONTAL_AXIS> {
    using type = DirectionAxis;
};
template <> struct TypeFrom<Property::AXIS> {
    using type = DirectionAxis;
};
template <> struct TypeFrom<Property::ORIENTATION> {
    using type = JigsawOrientation;
};
template <> struct TypeFrom<Property::FACE> {
    using type = AttachFace;
};
template <> struct TypeFrom<Property::BELL_ATTACHMENT> {
    using type = BellAttachment;
};
template <> struct TypeFrom<Property::WALL_HEIGHT_EAST> {
    using type = WallHeight;
};
template <> struct TypeFrom<Property::WALL_HEIGHT_NORTH> {
    using type = WallHeight;
};
template <> struct TypeFrom<Property::WALL_HEIGHT_SOUTH> {
    using type = WallHeight;
};
template <> struct TypeFrom<Property::WALL_HEIGHT_WEST> {
    using type = WallHeight;
};
template <> struct TypeFrom<Property::REDSTONE_EAST> {
    using type = RedstoneSide;
};
template <> struct TypeFrom<Property::REDSTONE_NORTH> {
    using type = RedstoneSide;
};
template <> struct TypeFrom<Property::REDSTONE_SOUTH> {
    using type = RedstoneSide;
};
template <> struct TypeFrom<Property::REDSTONE_WEST> {
    using type = RedstoneSide;
};
template <> struct TypeFrom<Property::DOUBLE_BLOCK_HALF> {
    using type = DoubleBlockHalf;
};
template <> struct TypeFrom<Property::HALF> {
    using type = Half;
};
template <> struct TypeFrom<Property::RAIL_SHAPE> {
    using type = RailShape;
};
template <> struct TypeFrom<Property::RAIL_SHAPE_STRAIGHT> {
    using type = RailShape;
};
template <> struct TypeFrom<Property::BED_PART> {
    using type = BedPart;
};
template <> struct TypeFrom<Property::CHEST_TYPE> {
    using type = ChestType;
};
template <> struct TypeFrom<Property::COMPARATOR_MODE> {
    using type = ComparatorMode;
};
template <> struct TypeFrom<Property::DOOR_HINGE> {
    using type = DoorHingeSide;
};
template <> struct TypeFrom<Property::NOTE_BLOCK_INSTRUMENT> {
    using type = NoteBlockInstrument;
};
template <> struct TypeFrom<Property::PISTON_TYPE> {
    using type = PistonType;
};
template <> struct TypeFrom<Property::SLAB_TYPE> {
    using type = SlabType;
};
template <> struct TypeFrom<Property::STAIRS_SHAPE> {
    using type = StairsShape;
};
template <> struct TypeFrom<Property::STRUCTURE_BLOCK_MODE> {
    using type = StructureMode;
};
template <> struct TypeFrom<Property::BAMBOO_LEAVES> {
    using type = BambooLeaves;
};
template <> struct TypeFrom<Property::AGE_0_1> {
    using type = int;
};
template <> struct TypeFrom<Property::AGE_0_2> {
    using type = int;
};
template <> struct TypeFrom<Property::AGE_0_3> {
    using type = int;
};
template <> struct TypeFrom<Property::AGE_0_5> {
    using type = int;
};
template <> struct TypeFrom<Property::AGE_0_7> {
    using type = int;
};
template <> struct TypeFrom<Property::AGE_0_15> {
    using type = int;
};
template <> struct TypeFrom<Property::AGE_0_25> {
    using type = int;
};
template <> struct TypeFrom<Property::BITES_0_6> {
    using type = int;
};
template <> struct TypeFrom<Property::DELAY_1_4> {
    using type = int;
};
template <> struct TypeFrom<Property::DISTANCE_1_7> {
    using type = int;
};
template <> struct TypeFrom<Property::EGGS_1_4> {
    using type = int;
};
template <> struct TypeFrom<Property::HATCH_0_2> {
    using type = int;
};
template <> struct TypeFrom<Property::LAYERS_1_8> {
    using type = int;
};
template <> struct TypeFrom<Property::LEVEL_0_3> {
    using type = int;
};
template <> struct TypeFrom<Property::LEVEL_0_8> {
    using type = int;
};
template <> struct TypeFrom<Property::LEVEL_1_8> {
    using type = int;
};
template <> struct TypeFrom<Property::HONEY_LEVEL> {
    using type = int;
};
template <> struct TypeFrom<Property::LEVEL_0_15> {
    using type = int;
};
template <> struct TypeFrom<Property::MOISTURE_0_7> {
    using type = int;
};
template <> struct TypeFrom<Property::NOTE_0_24> {
    using type = int;
};
template <> struct TypeFrom<Property::PICKLES_1_4> {
    using type = int;
};
template <> struct TypeFrom<Property::POWER_0_15> {
    using type = int;
};
template <> struct TypeFrom<Property::STAGE_0_1> {
    using type = int;
};
template <> struct TypeFrom<Property::DISTANCE_0_7> {
    using type = int;
};
template <> struct TypeFrom<Property::CHARGES> {
    using type = int;
};
template <> struct TypeFrom<Property::ROTATION_0_15> {
    using type = int;
};

struct PropertyUtil {
    static auto name(Property property) -> std::string;
    static auto values(Property property) -> std::span<const PropertyValue>;
    static auto parse(Property property, const Nbt::Tag& tag) -> tl::optional<PropertyValue>;
    static auto write(Property property, const PropertyValue& value) -> tl::optional<Nbt::Tag>;
    static auto string(const PropertyValue& value) -> tl::optional<std::string>;
};


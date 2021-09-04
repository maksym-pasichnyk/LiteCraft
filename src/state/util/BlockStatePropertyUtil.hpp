#pragma once

#include <nbt/nbt.hpp>
#include <state/Property.hpp>
#include <state/BlockStateProperties.hpp>

template <BlockStateProperty> struct TypeFrom;

template <> struct TypeFrom<BlockStateProperty::ATTACHED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::BOTTOM> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::CONDITIONAL> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::DISARMED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::DRAG> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::ENABLED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::EXTENDED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::EYE> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::FALLING> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::HANGING> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::HAS_BOTTLE_0> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::HAS_BOTTLE_1> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::HAS_BOTTLE_2> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::HAS_RECORD> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::HAS_BOOK> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::INVERTED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::IN_WALL> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::LIT> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::LOCKED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::OCCUPIED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::OPEN> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::PERSISTENT> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::POWERED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::SHORT> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::SIGNAL_FIRE> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::SNOWY> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::TRIGGERED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::UNSTABLE> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::WATERLOGGED> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::VINE_END> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::UP> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::DOWN> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::NORTH> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::EAST> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::SOUTH> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::WEST> {
    using type = bool;
};
template <> struct TypeFrom<BlockStateProperty::FACING> {
    using type = Direction;
};
template <> struct TypeFrom<BlockStateProperty::FACING_EXCEPT_UP> {
    using type = Direction;
};
template <> struct TypeFrom<BlockStateProperty::HORIZONTAL_FACING> {
    using type = Direction;
};
template <> struct TypeFrom<BlockStateProperty::HORIZONTAL_AXIS> {
    using type = DirectionAxis;
};
template <> struct TypeFrom<BlockStateProperty::AXIS> {
    using type = DirectionAxis;
};
template <> struct TypeFrom<BlockStateProperty::ORIENTATION> {
    using type = JigsawOrientation;
};
template <> struct TypeFrom<BlockStateProperty::FACE> {
    using type = AttachFace;
};
template <> struct TypeFrom<BlockStateProperty::BELL_ATTACHMENT> {
    using type = BellAttachment;
};
template <> struct TypeFrom<BlockStateProperty::WALL_HEIGHT_EAST> {
    using type = WallHeight;
};
template <> struct TypeFrom<BlockStateProperty::WALL_HEIGHT_NORTH> {
    using type = WallHeight;
};
template <> struct TypeFrom<BlockStateProperty::WALL_HEIGHT_SOUTH> {
    using type = WallHeight;
};
template <> struct TypeFrom<BlockStateProperty::WALL_HEIGHT_WEST> {
    using type = WallHeight;
};
template <> struct TypeFrom<BlockStateProperty::REDSTONE_EAST> {
    using type = RedstoneSide;
};
template <> struct TypeFrom<BlockStateProperty::REDSTONE_NORTH> {
    using type = RedstoneSide;
};
template <> struct TypeFrom<BlockStateProperty::REDSTONE_SOUTH> {
    using type = RedstoneSide;
};
template <> struct TypeFrom<BlockStateProperty::REDSTONE_WEST> {
    using type = RedstoneSide;
};
template <> struct TypeFrom<BlockStateProperty::DOUBLE_BLOCK_HALF> {
    using type = DoubleBlockHalf;
};
template <> struct TypeFrom<BlockStateProperty::HALF> {
    using type = Half;
};
template <> struct TypeFrom<BlockStateProperty::RAIL_SHAPE> {
    using type = RailShape;
};
template <> struct TypeFrom<BlockStateProperty::RAIL_SHAPE_STRAIGHT> {
    using type = RailShape;
};
template <> struct TypeFrom<BlockStateProperty::BED_PART> {
    using type = BedPart;
};
template <> struct TypeFrom<BlockStateProperty::CHEST_TYPE> {
    using type = ChestType;
};
template <> struct TypeFrom<BlockStateProperty::COMPARATOR_MODE> {
    using type = ComparatorMode;
};
template <> struct TypeFrom<BlockStateProperty::DOOR_HINGE> {
    using type = DoorHingeSide;
};
template <> struct TypeFrom<BlockStateProperty::NOTE_BLOCK_INSTRUMENT> {
    using type = NoteBlockInstrument;
};
template <> struct TypeFrom<BlockStateProperty::PISTON_TYPE> {
    using type = PistonType;
};
template <> struct TypeFrom<BlockStateProperty::SLAB_TYPE> {
    using type = SlabType;
};
template <> struct TypeFrom<BlockStateProperty::STAIRS_SHAPE> {
    using type = StairsShape;
};
template <> struct TypeFrom<BlockStateProperty::STRUCTURE_BLOCK_MODE> {
    using type = StructureMode;
};
template <> struct TypeFrom<BlockStateProperty::BAMBOO_LEAVES> {
    using type = BambooLeaves;
};
template <> struct TypeFrom<BlockStateProperty::AGE_0_1> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::AGE_0_2> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::AGE_0_3> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::AGE_0_5> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::AGE_0_7> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::AGE_0_15> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::AGE_0_25> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::BITES_0_6> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::DELAY_1_4> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::DISTANCE_1_7> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::EGGS_1_4> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::HATCH_0_2> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::LAYERS_1_8> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::LEVEL_0_3> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::LEVEL_0_8> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::LEVEL_1_8> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::HONEY_LEVEL> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::LEVEL_0_15> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::MOISTURE_0_7> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::NOTE_0_24> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::PICKLES_1_4> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::POWER_0_15> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::STAGE_0_1> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::DISTANCE_0_7> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::CHARGES> {
    using type = int;
};
template <> struct TypeFrom<BlockStateProperty::ROTATION_0_15> {
    using type = int;
};

struct BlockStatePropertyUtil {
    static auto name(BlockStateProperty property) -> std::optional<std::string>;
    static auto parse(BlockStateProperty property, const Nbt::Tag& tag) -> std::optional<Property>;
    static auto write(BlockStateProperty property, const Property& value) -> std::optional<Nbt::Tag>;
};


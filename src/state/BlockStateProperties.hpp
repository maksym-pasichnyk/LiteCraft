#pragma once

#include <state/Property.hpp>

enum class BlockStateProperty {
    // BooleanProperty
    ATTACHED,
    BOTTOM,
    CONDITIONAL,
    DISARMED,
    DRAG,
    ENABLED,
    EXTENDED,
    EYE,
    FALLING,
    HANGING,
    HAS_BOTTLE_0,
    HAS_BOTTLE_1,
    HAS_BOTTLE_2,
    HAS_RECORD,
    HAS_BOOK,
    INVERTED,
    IN_WALL,
    LIT,
    LOCKED,
    OCCUPIED,
    OPEN,
    PERSISTENT,
    POWERED,
    SHORT,
    SIGNAL_FIRE,
    SNOWY,
    TRIGGERED,
    UNSTABLE,
    WATERLOGGED,
    VINE_END,
    UP,
    DOWN,
    NORTH,
    EAST,
    SOUTH,
    WEST,
    // DirectionProperty
    FACING,
    FACING_EXCEPT_UP,
    HORIZONTAL_FACING,
    // EnumProperty
    HORIZONTAL_AXIS,
    AXIS,
    ORIENTATION,
    FACE,
    BELL_ATTACHMENT,
    WALL_HEIGHT_EAST,
    WALL_HEIGHT_NORTH,
    WALL_HEIGHT_SOUTH,
    WALL_HEIGHT_WEST,
    REDSTONE_EAST,
    REDSTONE_NORTH,
    REDSTONE_SOUTH,
    REDSTONE_WEST,
    DOUBLE_BLOCK_HALF,
    HALF,
    RAIL_SHAPE,
    RAIL_SHAPE_STRAIGHT,
    BED_PART,
    CHEST_TYPE,
    COMPARATOR_MODE,
    DOOR_HINGE,
    NOTE_BLOCK_INSTRUMENT,
    PISTON_TYPE,
    SLAB_TYPE,
    STAIRS_SHAPE,
    STRUCTURE_BLOCK_MODE,
    BAMBOO_LEAVES,
    // IntegerProperty
    AGE_0_1,
    AGE_0_2,
    AGE_0_3,
    AGE_0_5,
    AGE_0_7,
    AGE_0_15,
    AGE_0_25,
    BITES_0_6,
    DELAY_1_4,
    DISTANCE_1_7,
    EGGS_1_4,
    HATCH_0_2,
    LAYERS_1_8,
    LEVEL_0_3,
    LEVEL_0_8,
    LEVEL_1_8,
    HONEY_LEVEL,
    LEVEL_0_15,
    MOISTURE_0_7,
    NOTE_0_24,
    PICKLES_1_4,
    POWER_0_15,
    STAGE_0_1,
    DISTANCE_0_7,
    CHARGES,
    ROTATION_0_15,
};

template <BlockStateProperty T>
struct BlockStatePropertyType;

template <> struct BlockStatePropertyType<BlockStateProperty::ATTACHED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::BOTTOM> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::CONDITIONAL> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::DISARMED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::DRAG> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::ENABLED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::EXTENDED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::EYE> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::FALLING> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HANGING> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HAS_BOTTLE_0> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HAS_BOTTLE_1> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HAS_BOTTLE_2> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HAS_RECORD> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HAS_BOOK> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::INVERTED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::IN_WALL> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::LIT> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::LOCKED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::OCCUPIED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::OPEN> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::PERSISTENT> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::POWERED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::SHORT> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::SIGNAL_FIRE> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::SNOWY> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::TRIGGERED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::UNSTABLE> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::WATERLOGGED> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::VINE_END> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::UP> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::DOWN> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::NORTH> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::EAST> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::SOUTH> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::WEST> {
    using type = bool;
};
template <> struct BlockStatePropertyType<BlockStateProperty::FACING> {
    using type = Direction;
};
template <> struct BlockStatePropertyType<BlockStateProperty::FACING_EXCEPT_UP> {
    using type = Direction;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HORIZONTAL_FACING> {
    using type = Direction;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HORIZONTAL_AXIS> {
    using type = DirectionAxis;
};
template <> struct BlockStatePropertyType<BlockStateProperty::AXIS> {
    using type = DirectionAxis;
};
template <> struct BlockStatePropertyType<BlockStateProperty::ORIENTATION> {
    using type = JigsawOrientation;
};
template <> struct BlockStatePropertyType<BlockStateProperty::FACE> {
    using type = AttachFace;
};
template <> struct BlockStatePropertyType<BlockStateProperty::BELL_ATTACHMENT> {
    using type = BellAttachment;
};
template <> struct BlockStatePropertyType<BlockStateProperty::WALL_HEIGHT_EAST> {
    using type = WallHeight;
};
template <> struct BlockStatePropertyType<BlockStateProperty::WALL_HEIGHT_NORTH> {
    using type = WallHeight;
};
template <> struct BlockStatePropertyType<BlockStateProperty::WALL_HEIGHT_SOUTH> {
    using type = WallHeight;
};
template <> struct BlockStatePropertyType<BlockStateProperty::WALL_HEIGHT_WEST> {
    using type = WallHeight;
};
template <> struct BlockStatePropertyType<BlockStateProperty::REDSTONE_EAST> {
    using type = RedstoneSide;
};
template <> struct BlockStatePropertyType<BlockStateProperty::REDSTONE_NORTH> {
    using type = RedstoneSide;
};
template <> struct BlockStatePropertyType<BlockStateProperty::REDSTONE_SOUTH> {
    using type = RedstoneSide;
};
template <> struct BlockStatePropertyType<BlockStateProperty::REDSTONE_WEST> {
    using type = RedstoneSide;
};
template <> struct BlockStatePropertyType<BlockStateProperty::DOUBLE_BLOCK_HALF> {
    using type = DoubleBlockHalf;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HALF> {
    using type = Half;
};
template <> struct BlockStatePropertyType<BlockStateProperty::RAIL_SHAPE> {
    using type = RailShape;
};
template <> struct BlockStatePropertyType<BlockStateProperty::RAIL_SHAPE_STRAIGHT> {
    using type = RailShape;
};
template <> struct BlockStatePropertyType<BlockStateProperty::BED_PART> {
    using type = BedPart;
};
template <> struct BlockStatePropertyType<BlockStateProperty::CHEST_TYPE> {
    using type = ChestType;
};
template <> struct BlockStatePropertyType<BlockStateProperty::COMPARATOR_MODE> {
    using type = ComparatorMode;
};
template <> struct BlockStatePropertyType<BlockStateProperty::DOOR_HINGE> {
    using type = DoorHingeSide;
};
template <> struct BlockStatePropertyType<BlockStateProperty::NOTE_BLOCK_INSTRUMENT> {
    using type = NoteBlockInstrument;
};
template <> struct BlockStatePropertyType<BlockStateProperty::PISTON_TYPE> {
    using type = PistonType;
};
template <> struct BlockStatePropertyType<BlockStateProperty::SLAB_TYPE> {
    using type = SlabType;
};
template <> struct BlockStatePropertyType<BlockStateProperty::STAIRS_SHAPE> {
    using type = StairsShape;
};
template <> struct BlockStatePropertyType<BlockStateProperty::STRUCTURE_BLOCK_MODE> {
    using type = StructureMode;
};
template <> struct BlockStatePropertyType<BlockStateProperty::BAMBOO_LEAVES> {
    using type = BambooLeaves;
};
template <> struct BlockStatePropertyType<BlockStateProperty::AGE_0_1> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::AGE_0_2> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::AGE_0_3> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::AGE_0_5> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::AGE_0_7> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::AGE_0_15> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::AGE_0_25> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::BITES_0_6> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::DELAY_1_4> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::DISTANCE_1_7> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::EGGS_1_4> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HATCH_0_2> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::LAYERS_1_8> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::LEVEL_0_3> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::LEVEL_0_8> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::LEVEL_1_8> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::HONEY_LEVEL> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::LEVEL_0_15> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::MOISTURE_0_7> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::NOTE_0_24> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::PICKLES_1_4> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::POWER_0_15> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::STAGE_0_1> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::DISTANCE_0_7> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::CHARGES> {
    using type = int;
};
template <> struct BlockStatePropertyType<BlockStateProperty::ROTATION_0_15> {
    using type = int;
};
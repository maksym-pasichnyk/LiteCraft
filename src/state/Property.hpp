#pragma once

#include <util/Direction.hpp>

#include <state/Half.hpp>
#include <state/BedPart.hpp>
#include <state/SlabType.hpp>
#include <state/ChestType.hpp>
#include <state/RailShape.hpp>
#include <state/WallHeight.hpp>
#include <state/PistonType.hpp>
#include <state/AttachFace.hpp>
#include <state/StairsShape.hpp>
#include <state/RedstoneSide.hpp>
#include <state/BambooLeaves.hpp>
#include <state/DoorHingeSide.hpp>
#include <state/StructureMode.hpp>
#include <state/ComparatorMode.hpp>
#include <state/BellAttachment.hpp>
#include <state/DoubleBlockHalf.hpp>
#include <state/JigsawOrientation.hpp>
#include <state/NoteBlockInstrument.hpp>
#include <variant>

using Property = std::variant<
    int,
    bool,
    Half,
    BedPart,
    SlabType,
    ChestType,
    RailShape,
    WallHeight,
    PistonType,
    AttachFace,
    Direction,
    StairsShape,
    RedstoneSide,
    BambooLeaves,
    DirectionAxis,
    DoorHingeSide,
    StructureMode,
    ComparatorMode,
    BellAttachment,
    DoubleBlockHalf,
    JigsawOrientation,
    NoteBlockInstrument
>;
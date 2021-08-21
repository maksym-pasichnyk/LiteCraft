#pragma once

enum class JigsawOrientation {
    DOWN_EAST, //("down_east", Direction.DOWN, Direction.EAST),
    DOWN_NORTH, //("down_north", Direction.DOWN, Direction.NORTH),
    DOWN_SOUTH, //("down_south", Direction.DOWN, Direction.SOUTH),
    DOWN_WEST, //("down_west", Direction.DOWN, Direction.WEST),
    UP_EAST, //("up_east", Direction.UP, Direction.EAST),
    UP_NORTH, //("up_north", Direction.UP, Direction.NORTH),
    UP_SOUTH, //("up_south", Direction.UP, Direction.SOUTH),
    UP_WEST, //("up_west", Direction.UP, Direction.WEST),
    WEST_UP, //("west_up", Direction.WEST, Direction.UP),
    EAST_UP, //("east_up", Direction.EAST, Direction.UP),
    NORTH_UP, //("north_up", Direction.NORTH, Direction.UP),
    SOUTH_UP, //("south_up", Direction.SOUTH, Direction.UP);
};
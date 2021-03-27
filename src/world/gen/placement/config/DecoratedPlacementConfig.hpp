#pragma once

struct ConfiguredPlacement;
struct DecoratedPlacementConfig {
    ConfiguredPlacement* outer;
    ConfiguredPlacement* inner;
};
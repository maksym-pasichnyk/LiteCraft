#pragma once

#include <util/math/BlockPos.hpp>
#include <tl/optional.hpp>

struct EndGatewayConfig {
    tl::optional<BlockPos> exit;
    bool exact;
};
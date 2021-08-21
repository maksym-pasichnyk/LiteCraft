#pragma once

#include <util/math/BlockPos.hpp>
#include <optional>

struct EndGatewayConfig {
    std::optional<BlockPos> exit;
    bool exact;
};
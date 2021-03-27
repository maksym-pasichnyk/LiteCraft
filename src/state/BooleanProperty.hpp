#pragma once

#include "Property.hpp"

struct BooleanProperty : Property {
    auto create() -> BooleanProperty* {
        return nullptr;
    }
};
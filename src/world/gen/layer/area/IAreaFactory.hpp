#pragma once

#include "IArea.hpp"

#include <memory>
#include <functional>

struct IAreaFactory : private std::function<IArea()> {
    using function::function;

    IArea makeArea() {
        return (*this)();
    }
};
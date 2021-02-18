#pragma once

#include "IArea.hpp"

#include <memory>
#include <functional>

template <IArea T>
struct IAreaFactory : private std::function<T()> {
    using std::function<T()>::function;

    T makeArea() {
        return (*this)();
    }
};
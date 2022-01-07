#pragma once

#include <type_traits>

template <typename Self>
struct Trait;

template <typename Self>
Trait(Self&& self) -> Trait<std::decay_t<Self>>;
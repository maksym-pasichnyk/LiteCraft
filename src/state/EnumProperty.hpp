#pragma once

#include <concepts>

template <typename T> requires std::is_enum_v<T>
struct EnumProperty {

};
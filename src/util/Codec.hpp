#pragma once

#include <tl/optional.hpp>
#include <nbt/nbt.hpp>

template <typename T>
struct Codec {
    auto (*parse)(const Nbt::Tag& tag) -> tl::optional<T> = nullptr;
    auto (*write)(const T& value) -> tl::optional<Nbt::Tag> = nullptr;
};

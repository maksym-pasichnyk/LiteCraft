#pragma once

#include <optional>
#include <nbt/nbt.hpp>

template <typename T>
struct Codec {
    auto (*parse)(const Nbt::Tag& tag) -> std::optional<T> = nullptr;
    auto (*write)(const T& value) -> std::optional<Nbt::Tag> = nullptr;
};

#pragma once

#include <optional>
#include <nbt/nbt.hpp>

template <typename T>
struct Codec {
    auto (*parse)(const Tag& tag) -> std::optional<T> = nullptr;
    auto (*write)(const T& value) -> std::optional<Tag> = nullptr;
};

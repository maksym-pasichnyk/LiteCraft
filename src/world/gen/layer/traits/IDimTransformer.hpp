#pragma once

#include <concepts>

template <typename T>
concept cIDimTransformer = requires(T& self, int x, int z) {
    {self.getOffsetX(x)} -> std::same_as<int>;
    {self.getOffsetZ(x)} -> std::same_as<int>;
};
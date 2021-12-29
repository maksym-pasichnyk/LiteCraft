#pragma once

#include <filesystem>
#include <tl/optional.hpp>
#include <fstream>
#include <sstream>
#include <string>

struct AppPlatform {
    static auto readFile(const std::filesystem::path& path) -> tl::optional<std::string> {
        if (std::ifstream file{path, std::ios::in}) {
            std::stringstream stream{};
            stream << file.rdbuf();
            file.close();
            return stream.str();
        }
        return tl::nullopt;
    }
};

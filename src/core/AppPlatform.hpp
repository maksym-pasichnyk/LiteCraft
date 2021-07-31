#pragma once

#include <filesystem>
#include <optional>
#include <fstream>
#include <sstream>
#include <string>

struct AppPlatform {
    static auto readFile(const std::filesystem::path& path) -> std::optional<std::string> {
        if (std::ifstream file{path, std::ios::in}) {
            std::stringstream stream{};
            stream << file.rdbuf();
            file.close();
            return stream.str();
        }
        return std::nullopt;
    }
};

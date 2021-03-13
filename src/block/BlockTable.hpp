#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <unordered_map>

struct BlockTable {
    BlockTable(const BlockTable&) = delete;
    BlockTable& operator=(const BlockTable&) = delete;

    std::vector<std::string> id_to_name{};
    std::unordered_map<std::string, int32_t> name_to_id{};

    BlockTable() {
        id_to_name.emplace_back("air");
        name_to_id.emplace("air", 0);
    }

    int32_t getId(std::string name) {
        auto it = name_to_id.find(name);
        if (it != name_to_id.end()) {
            return it->second;
        }

        auto id = static_cast<int32_t>(id_to_name.size());

        id_to_name.emplace_back(name);
        name_to_id.emplace(std::move(name), id);

        return id;
    }

    std::string_view getName(int32_t id) {
        return id_to_name.at(static_cast<size_t>(id));
    }
};


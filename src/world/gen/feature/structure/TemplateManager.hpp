#pragma once

#include <ResourceManager.hpp>
#include <map>
#include <memory>
#include <optional>
#include <string>

struct Template final {
    Template() = default;
    Template(const Template&) = delete;
    Template& operator=(const Template&) = delete;
};

struct TemplateManager {
    TemplateManager(ResourceManager& resources) : resources(resources) {}

    auto get(const std::string& name) -> Template* {
        auto& structure = templates[name];
        if (structure == nullptr) {
            structure = load(name).value_or(std::make_unique<Template>());
        }
        return structure.get();
    }

private:
    ResourceManager& resources;

    auto load(const std::string& name) -> std::optional<std::unique_ptr<Template>> {
        if (auto resource = resources.open(fmt::format("structures/{}.nbt", name))) {
            return readStructure(*resource->io);
        }
        return std::nullopt;
    }

    auto readStructure(std::istream& io) -> std::optional<std::unique_ptr<Template>> {
        return std::nullopt;
    }

    std::map<std::string, std::unique_ptr<Template>> templates;
};
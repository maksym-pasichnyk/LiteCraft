#pragma once

#include <util/Registry.hpp>

struct Json;
struct ModelFormat;
struct ResourcePackManager;

struct Models {
    static Registry<ModelFormat> models;

    static void parse(const Json& obj);
    static void init(ResourcePackManager& resources);
};
#include "Structures.hpp"
#include "MineshaftStructure.hpp"

std::map<std::string, std::unique_ptr<Structure>> Structures::registry;
std::vector<std::vector<Structure*>> Structures::stages;

Structure* Structures::MINESHAFT;

template <typename T, typename... Args>
inline T* createStructure(std::string name, GenerationStage::Decoration stage, Args&&... args) {
    if (Structures::stages.size() < static_cast<int>(stage) + 1) {
        Structures::stages.resize(static_cast<int>(stage) + 1);
    }

    auto structure = new T(std::forward<Args>(args)...);
    Structures::registry.emplace(std::move(name), structure);
    Structures::stages[static_cast<int>(stage)].emplace_back(structure);
    return structure;
}

void Structures::registerStructures() {
    MINESHAFT = createStructure<MineshaftStructure>("mineshaft", GenerationStage::Decoration::UNDERGROUND_STRUCTURES);
}

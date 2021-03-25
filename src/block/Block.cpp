#include "Block.hpp"

Block::Block(int id) : id(id) {}

Block::Block(int id, Material* material) : id(id), material(material) {}

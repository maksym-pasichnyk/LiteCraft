#pragma once

#include <resources/ResourceLocation.hpp>

struct Shader : Resource {
	GLuint id;

	explicit Shader(GLuint id) : id(id) {}
};
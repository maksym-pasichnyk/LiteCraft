#version 450

out gl_PerVertex {
	vec4 gl_Position;
};

layout(push_constant) uniform CameraConstants {
	mat4 transform;
	vec3 position;
} constants;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inCoords;

layout(location = 0) out vec3 vertex;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec2 coords;

// layout(location = 0) uniform mat4 model_transform;

void main() {
	gl_Position = constants.transform * /*model_transform **/ vec4(inPosition, 1.0);

	vertex = inPosition;
	normal = inNormal;
	coords = inCoords;
}
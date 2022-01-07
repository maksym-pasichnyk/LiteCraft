#version 450 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tex;
layout(location = 2) in vec4 in_color;
layout(location = 3) in vec4 in_light;

out gl_PerVertex {
	vec4 gl_Position;
};

layout(binding = 0) uniform UniformBufferObject {
	mat4 _CameraLocalToMatrix;
	vec4 _CameraPosition;
};

layout(location = 0) out struct {
	vec4 color;
	vec2 tex;
} v_out;

void main() {
	v_out.color = vec4(in_color.rgb, max(in_light.x, in_light.w) * in_color.a);
	v_out.tex = in_tex;

	gl_Position = _CameraLocalToMatrix * vec4(in_pos, 1);
}
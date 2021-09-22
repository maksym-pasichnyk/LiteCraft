#version 450

out gl_PerVertex {
	vec4 gl_Position;
};

layout(binding = 0) uniform CameraConstants {
	mat4 transform;
	vec3 position;
} constants;

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tex;
layout(location = 2) in vec4 in_color;
layout(location = 3) in vec4 in_light;

layout(location = 0) out struct {
	vec4 color;
	vec2 tex;
} v_out;

void main() {
	gl_Position = constants.transform * vec4(in_pos, 1);

	v_out.color = vec4(in_color.rgb, max(in_light.x, in_light.w) * in_color.a);
	v_out.tex = in_tex;
}
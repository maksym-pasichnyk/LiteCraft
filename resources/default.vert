#version 450

out gl_PerVertex {
	vec4 gl_Position;
};

layout (binding = 0) uniform CameraConstants {
	mat4 transform;
	vec3 position;
} camera;

layout (location = 0) in vec3 in_point;
layout (location = 1) in vec2 in_tex;
layout (location = 2) in vec4 in_color;

layout (location = 0) out struct {
	vec4 color;
	vec2 tex;
	vec4 fogColor;
} v_out;

void main() {
	gl_Position = camera.transform * vec4(in_point, 1.0);

	v_out.color = in_color;
	v_out.tex = in_tex;

	vec3 FOG_COLOR = vec3(0, 0.68, 1.0);
	float RENDER_DISTANCE = 8.0f;
	vec2 FOG_CONTROL = vec2(9, 13);

	vec3 relPos = camera.position - in_point.xyz;
	float cameraDepth = length(relPos);
	float len = cameraDepth / RENDER_DISTANCE;

	v_out.fogColor.rgb = FOG_COLOR.rgb;
	v_out.fogColor.a = clamp((len - FOG_CONTROL.x) / (FOG_CONTROL.y - FOG_CONTROL.x), 0.0, 1.0);
}
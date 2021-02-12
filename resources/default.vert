#version 450

out gl_PerVertex {
	vec4 gl_Position;
};

layout (binding = 0) uniform CameraConstants {
	mat4 transform;
	vec3 position;
} camera;

layout(location = 0) uniform vec3 FOG_COLOR;
layout(location = 4) uniform vec2 FOG_CONTROL;
layout(location = 7) uniform float RENDER_DISTANCE = 8.0f;

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

	int light = int(in_color.a * 255);
	float block_light = float(light & 15);
	float sky_light = float((light >> 4) & 15);

	v_out.color = vec4(in_color.rgb, max(block_light, sky_light) / 15.0f);
	v_out.tex = in_tex;

	vec3 relPos = camera.position - in_point.xyz;
	float cameraDepth = length(relPos);
	float len = cameraDepth / RENDER_DISTANCE;

	v_out.fogColor.rgb = FOG_COLOR.rgb;
	v_out.fogColor.a = clamp((len - FOG_CONTROL.x) / (FOG_CONTROL.y - FOG_CONTROL.x), 0.0, 1.0);
}
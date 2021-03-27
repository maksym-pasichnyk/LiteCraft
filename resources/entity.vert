#version 450

out gl_PerVertex {
	vec4 gl_Position;
};

layout (binding = 0) uniform CameraConstants {
	mat4 transform;
	vec3 position;
	vec3 FOG_COLOR;
	vec2 FOG_CONTROL;
	float RENDER_DISTANCE;
} camera;

layout(location = 0) uniform mat4 model_transform;

layout (location = 0) in vec3 in_point;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_coords;

layout (location = 0) out struct {
	vec3 normal;
	vec2 coords;
	vec4 fogColor;
} v_out;

void main() {
	gl_Position = camera.transform * model_transform * vec4(in_point, 1.0);

	v_out.normal = in_normal;
	v_out.coords = in_coords;

	vec3 relPos = camera.position - in_point.xyz;
	float cameraDepth = length(relPos);
	float len = cameraDepth / camera.RENDER_DISTANCE;

	v_out.fogColor.rgb = camera.FOG_COLOR;
	v_out.fogColor.a = clamp((len - camera.FOG_CONTROL.x) / (camera.FOG_CONTROL.y - camera.FOG_CONTROL.x), 0.0, 1.0);
}
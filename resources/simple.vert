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
layout (location = 3) in vec4 in_light;

layout (location = 0) out vec4 out_color;

void main() {
    gl_Position = camera.transform * vec4(in_point, 1.0);

    out_color = in_color;
}
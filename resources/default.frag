#version 450

layout(location = 0) out vec4 out_color;

layout(binding = 0) uniform sampler2D sTexture;

layout(location = 0) in struct {
    vec4 color;
    vec2 tex;
} v_in;

void main() {
    vec4 tex = texture(sTexture, v_in.tex);
    vec3 col = mix(tex.rgb, tex.rgb * v_in.color.rgb, tex.a);
    col *= vec3(v_in.color.a);

    out_color = vec4(col, 1.0);
}
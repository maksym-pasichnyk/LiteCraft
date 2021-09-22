#version 450

layout(location = 0) out vec4 out_color;

layout(binding = 0) uniform sampler2D sTexture;

layout(location = 0) in struct {
    vec4 color;
    vec2 tex;
} v_in;

void main() {
    vec4 tex = texture(sTexture, v_in.tex);
    vec4 col = tex;
    col.rgb *= v_in.color.rgb;
    col.rgb *= vec3(v_in.color.a);

    out_color = col;
}
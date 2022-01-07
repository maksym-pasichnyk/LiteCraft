#version 450

layout(location = 0) out vec4 out_color;

layout(location = 0) in struct {
    vec4 color;
    vec2 tex;
} v_in;

layout(binding = 1) uniform sampler2D sTexture;

void main() {
    vec4 tex = texture(sTexture, v_in.tex);
    if (tex.a < 0.5f) {
        discard;
    }

    vec3 col = tex.rgb;
    col *= v_in.color.rgb;
    col *= vec3(v_in.color.a);

    out_color = vec4(col, 1.0f);
}
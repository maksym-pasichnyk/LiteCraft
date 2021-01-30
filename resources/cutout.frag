#version 450

out vec4 out_color;

layout (binding = 0) uniform sampler2D sTexture;

layout (location = 0) in struct {
    vec4 color;
    vec2 tex;
	vec4 fogColor;
} v_in;

void main() {
    vec4 tex = texture(sTexture, v_in.tex);
    if (tex.a < 0.5f) {
        discard;
    }

    vec3 col = tex.rgb;
    col *= v_in.color.rgb;
    col *= vec3(v_in.color.a);

    float gamma = 1.3;
    col.rgb = pow(col.rgb, vec3(gamma));
    out_color = vec4(col, 1.0);
}
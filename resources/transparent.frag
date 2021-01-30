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
    vec4 col = tex;
    col.rgb *= v_in.color.rgb;
    col.rgb *= vec3(v_in.color.a);

    float gamma = 1.3;
    col.rgb = pow(col.rgb, vec3(gamma));
    col.rgb = mix(col.rgb, v_in.fogColor.rgb, v_in.fogColor.a);
    out_color = col;
}
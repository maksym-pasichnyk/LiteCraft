#version 450

out vec4 out_color;

layout (binding = 0) uniform sampler2D sTexture;

layout (location = 0) in struct {
    vec3 normal;
    vec2 coords;
    vec4 fogColor;
} v_in;

void main() {
    vec4 tex = texture(sTexture, v_in.coords);
    if (tex.a < 0.5f) {
        discard;
    }

    vec3 light_dir = normalize(vec3(-0.5, -0.5, -0.3));

    float diffuse = dot(v_in.normal.xyz, light_dir);

    vec3 col = tex.rgb;
    col *= diffuse;
//    col *= vec3(v_in.color.a);

//    vec3 col = mix(tex.rgb, tex.rgb * v_in.normal.rgb, tex.a);
//    col *= vec3(v_in.normal.a);
//
    float gamma = 1.3;
    col.rgb = pow(col.rgb, vec3(gamma));
    col.rgb = mix(col.rgb, v_in.fogColor.rgb, v_in.fogColor.a);
    out_color = vec4(col, 1.0);
}
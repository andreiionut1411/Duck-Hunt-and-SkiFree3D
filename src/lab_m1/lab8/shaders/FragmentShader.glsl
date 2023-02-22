#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform sampler2D texture;
uniform int moving;
uniform vec2 offset;
uniform float scale;

// We will use the Phong shading method
uniform vec3 light_position;
uniform vec3 light_direction;
uniform vec3 eye_position;
uniform vec3 object_color;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// Output
layout(location = 0) out vec4 out_color;


void main()
{   

    out_color = vec4(object_color, 1);
    // We calculate the lighting

    vec3 ambient_light = vec3(0.25 * material_kd);
    vec3 diffuse_light = vec3(0);
    vec3 specular_light = vec3(0);
    int recv_light = 0;

    vec3 L = normalize(light_position - world_position);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);

    float cutoff = radians(30.0f);
    float spot_light = dot (-L, light_direction);
    vec3 light;

    if (spot_light < cos(cutoff)) {
    light = vec3(0);
    }
    else {
        float spot_light_limit = cos(cutoff);
        float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);

        diffuse_light = vec3(1, 1, 1) * material_kd * max(dot(world_normal, L), 0);

        if (dot(world_normal, L) > 0) recv_light = 1;

        specular_light = vec3(1, 1, 1) * material_ks * recv_light * pow(max(dot(world_normal, H), 0), material_shininess);
        float k_c = 0;
        float k_l = 0;
        float k_p = 1;
        float factor = 1 / (k_c + k_l * distance(world_position, light_position) + k_p * pow(distance(world_position, light_position), 2));
        factor = pow (linear_att, 2);
        light = ambient_light + factor * (diffuse_light + specular_light);
    }

    out_color = out_color * 0.5 + vec4(light, 0);
}

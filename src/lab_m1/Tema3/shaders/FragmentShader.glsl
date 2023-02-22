#version 330

// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform sampler2D texture;
uniform int moving;
uniform vec2 offset;
uniform float scale;

// We will use the Phong shading method
// On the slope there will be max 100 objects on the slope,
// so max 100 point lights and max 200 spot lights.
uniform vec3 directional_light_direction;
uniform int number_of_point_lights;
uniform int number_of_spot_lights;
uniform vec3 point_light_position[100];
uniform vec3 light_color[100];
uniform vec3 spot_light_position[200];
uniform vec3 light_direction;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// Output
layout(location = 0) out vec4 out_color;

// The function calculates the diffuse and specular components of a light,
// given its position.
vec3 diffuseAndSpecularLight(vec3 position, vec3 light_color) {
    vec3 diffuse_light = vec3(0);
    vec3 specular_light = vec3(0);
    int recv_light = 0;

    vec3 L = normalize(position - world_position);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);
    diffuse_light = light_color * material_kd * max(dot(world_normal, L), 0);

    if (dot(world_normal, L) > 0) recv_light = 1;

    specular_light = light_color * material_ks * recv_light * pow(max(dot(world_normal, H), 0), material_shininess);

    return (diffuse_light + specular_light);
}

void main()
{   
    if (moving == 0) {
        out_color = texture2D(texture, texcoord);
    }
    else {
        // We divide by twice the scale of the quad because the quad is already a 2x2,
        // so in order to maintain the illusion that the ground is steady, we do this division
        out_color = texture2D(texture, texcoord + 1 / (2 * scale) * offset);
    }

    // We don't add ambient lighting for evey source of light because it will give
    // us a scene as a whole that will be brighter and brighter with each new light,
    // which is undesirable.
    vec3 ambient_light = vec3(0.25 * material_kd);

    // We dim the out_color, so the object is initially unlit.
    out_color = out_color * 0.22 + vec4(ambient_light, 1.0f);

    // We calculate the lighting from the directional light. For the sun
    // we will have a grayish light. We don't have a fully white light
    // because otherwise the scene would be too bright and the other lights
    // would lose their nice lighting.
    vec3 diffuse_light = vec3(0);
    vec3 specular_light = vec3(0);
    int recv_light = 0;

    vec3 L = normalize(-directional_light_direction);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);
    diffuse_light = vec3(0.2) * material_kd * max(dot(world_normal, L), 0);

     if (dot(world_normal, L) > 0) recv_light = 1;

    specular_light = vec3(0.2) * material_ks * recv_light * pow(max(dot(world_normal, H), 0), material_shininess);
    vec3 light = diffuse_light + specular_light;
    out_color = out_color + vec4(light, 0);

    // We calculate the lighting from the point lights.
    for (int i = 0; i < number_of_point_lights; i++) {
        // Not every object has a point light, so those that don't, have an illegal
        // light color, so we know to not calculate the lighting for objects that
        // don't emit lights, suck as rocks.
        if (light_color[i].x > 0) {
           vec3 difSpec = diffuseAndSpecularLight(point_light_position[i], light_color[i]);

            float k_c = 1;
            float k_l = 0.35;
            float k_p = 0.44;
            float factor = 1 / (k_c + k_l * distance(world_position, point_light_position[i]) + k_p * pow(distance(world_position, point_light_position[i]), 2));
            vec3 light = factor * difSpec;

            out_color = out_color + vec4(light, 0);
        }
    }

    // We calculate the lighting from the spot lights
    for (int i = 0; i < number_of_spot_lights; i++) {
        vec3 light_dir = normalize(light_direction);
        vec3 L = normalize(spot_light_position[i] - world_position);
        float cut_off = radians(25.0f);
        float spot_light = dot(-L, light_dir);
        float spot_light_limit = cos(cut_off);

        // If the fragment is within the light cone, then we calculate the lighting,
        // otherwise the fragment will not receive lighting from the spot light.
        if (spot_light > cos(cut_off))
        {
            // We use a different attenuation function for the spot, than for the point_lights
            // We also use a 0.8 factor to so that we don't get a very luminous center, given
            // the fact that we have a spot light that is at a slight angle.
	        float linear_att = 0.8 * (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float factor = pow(linear_att, 2);

            vec3 difSpec = diffuseAndSpecularLight(spot_light_position[i], vec3(1, 1, 1));
            vec3 light = factor * difSpec;
            out_color = out_color + vec4(light, 0);
        }
    }
}

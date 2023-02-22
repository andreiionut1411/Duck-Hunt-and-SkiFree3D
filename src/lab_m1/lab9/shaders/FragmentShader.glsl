#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int ciclare;
uniform float time;
// TODO(student): Declare various other uniforms

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.

    vec4 color1, color2;
    if (ciclare == 0) {
        color1 = texture2D(texture_1, texcoord);
        color2 = texture2D(texture_2, texcoord);
    }
    else {
        color1 = texture2D(texture_1, texcoord + vec2(time, 0));
        color2 = texture2D(texture_2, texcoord + vec2(time, 0));
    }
    vec4 color = mix(color1, color2, 0.5);

    if (color.a < 0.5) {
        discard;
    }
    
    
   out_color = color;

}

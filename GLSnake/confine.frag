#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoords;

uniform vec4 color;

uniform vec3 lightDirection;
uniform vec3 directedLightColor;
uniform vec3 ambientLightColor;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = color;
}
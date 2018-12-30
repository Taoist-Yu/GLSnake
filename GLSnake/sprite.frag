#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform vec4 color;
uniform sampler2D spriteSampler;

void main()
{    
	FragColor = texture(spriteSampler,TexCoords) * color;
}
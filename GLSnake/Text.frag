#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D spriteSampler;

void main()
{    
	vec4 color = texture(spriteSampler,TexCoords);
	if((color.r + color.g + color.b) > 2.8)
		color = vec4(0,0,0,0);
	FragColor = color;
}
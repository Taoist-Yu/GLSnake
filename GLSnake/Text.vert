#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform vec3 position;
uniform vec3 scale;

out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;
    gl_Position = vec4(aPos * scale + position, 1.0);
}
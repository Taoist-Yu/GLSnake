#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec2 TexCoords;
out vec3 poisonColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Normal = aNormal;
    TexCoords = aTexCoords;    
	poisonColor = (aPos + vec3(1,1,1))*0.5;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
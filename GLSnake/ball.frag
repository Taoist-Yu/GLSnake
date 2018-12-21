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
	vec4 objectColor = color;
	//diffuse caculate
	vec3 diffuse;
	{
		vec3 v1 = normalize(-lightDirection);
		vec3 v2 = normalize(Normal);
		float diff = max(dot(v1,v2),0.0f);
		diffuse = diff * directedLightColor;
	}
	//ambient 
	vec3 result = diffuse + ambientLightColor;
	result = min(result,1.0f);

    FragColor = vec4(result,1.0) * color;
}
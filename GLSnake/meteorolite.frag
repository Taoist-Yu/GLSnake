#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightDirection;
uniform vec3 directedLightColor;
uniform vec3 ambientLightColor;

void main()
{    
	vec4 objectColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//diffuse caculate
	vec3 diffuse;
	{
		vec3 v1 = normalize(-lightDirection);
		vec3 v2 = normalize(Normal);
		float diff = dot(v1,v2);
		diff = (diff + 1) / 2;
		diffuse = diff * directedLightColor;
	}
	//ambient 
	vec3 result = diffuse + ambientLightColor;
	result = min(result,1.0f);
	result = sqrt(result);

    FragColor = vec4(result,1.0) * objectColor;
	FragColor = mix(vec4(result,1.0f),objectColor,0.5);
}
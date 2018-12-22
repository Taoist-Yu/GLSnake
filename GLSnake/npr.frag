#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightDirection;
uniform vec3 directedLightColor;
uniform vec3 ambientLightColor;

uniform sampler2D texture_diffuse1;

float discretize(float value)
{
	if(value < 0.3)	
		value = 0.15;
	else if(value < 0.7)
		value = 0.5;
	else 
		value = 0.85;
		
	return value;
}

void main()
{    
	vec4 objectColor = texture(texture_diffuse1, TexCoords);
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

	result.r = discretize(result.r);
	result.g = discretize(result.g);
	result.b = discretize(result.b);

    FragColor = vec4(result,1.0f) * objectColor;
}
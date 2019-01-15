#version 330 core
in vec3 vecColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;  

void main()
{
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse);
	vec4 FragColor = vec4(result, 1.0);

	color = FragColor * texture(Texture0, TexCoord);
	if (TexCoord == vec2(-0.1f, -0.1f))
		color = vec4(vecColor * result, 1.0f);
}

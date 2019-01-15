#version 330 core
in vec3 vecColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture0;


void main()
{
	color = texture(Texture0, TexCoord);
	if (TexCoord == vec2(-0.1f, -0.1f))
		color = vec4(vecColor, 1.0f);
}


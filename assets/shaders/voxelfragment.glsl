#version 460 core

in vec4 outColor;

out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
	FragColor = outColor;
}
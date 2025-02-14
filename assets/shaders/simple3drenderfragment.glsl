#version 460 core
out vec4 FragColor;

in vec4 outColor;
in vec2 TextCoord;

uniform sampler2D Texture;

void main()
{
	FragColor = texture(Texture, TextCoord);
}

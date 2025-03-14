#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNorm;
layout (location = 3) in vec2 aTextCoord;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

out vec4 outColor;
out vec2 TextCoord;

void main()
{
	gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	outColor = aColor;
	TextCoord = aTextCoord;
}

#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNorm;

out vec4 outColor;

uniform vec3 color;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	outColor = vec4(color, 1.0);
}

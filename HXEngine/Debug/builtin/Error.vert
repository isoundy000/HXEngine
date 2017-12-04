#version 430 core

uniform mat4 mvp_matrix;

layout(location = 0) in vec4 vPosition;

void main()
{
	gl_Position = mvp_matrix * vPosition;
}
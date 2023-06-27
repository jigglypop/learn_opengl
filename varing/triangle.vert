#version 410 core

in vec4 vertexPos;
void main(void) { 
	gl_Position = vertexPos; 
}
#version 400 


out vec4 FragColor;


in vec3 FragPos; 
in vec2 TexCoords;

uniform vec4 objectColor;
  
void main()
{
	FragColor = objectColor;
}
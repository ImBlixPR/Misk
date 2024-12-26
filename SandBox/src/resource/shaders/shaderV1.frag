#version 400 


out vec4 FragColor;


in vec3 FragPos; 
in vec2 TexCoords;

uniform sampler2D tex;
  
void main()
{
	
	
	FragColor = vec4(vec3(texture(tex, TexCoords)), 1.0);
	//FragColor = vec4(1.0);

	//FragColor += vec4(normal, 1.0);

}
#pragma once

#include <vector>
#include <glm/glm.hpp>


struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};


namespace Misk{
	struct bufferObject {
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;

	};



	class Mesh {

	public:

		//defualt constructor
		Mesh();

		//main constructor
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>  indices);

		//things
		void initMesh();

		void DrawMesh();


	

		~Mesh();

	private:
		std::vector<Vertex> mVertices;
		std::vector<unsigned int> mIndices;

		//buffers object
		bufferObject mBufferObj;
	};



}
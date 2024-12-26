#include "Game.h"
#include <functional>

#include "stb_image.h"

void DrawObject(Misk::Mesh* mesh, Misk::Shader* shader)
{
	shader->use();
	mesh->DrawMesh();
}

#include "imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




float angle = 0.0f;
float speedAng = 10.0f;
float tempScal = 1.0f;
float tx = 30.0f;
float ty = 0.0f;
float tz = -2.0f;
const float toRadians = 3.14159265f / 180.0f;

/// <Gloabel varible>
//! Gloabel varible
glm::mat4 projection;
Misk::Camera camera;
Misk::Timestep deltaTime;


Misk::Texture* texture;


glm::vec3 lightPos(0.0f, 1.0f, -2.5f);
/// 
/// </Gloabel varible>




class MainLayer : public Misk::Layer
{
public:
	MainLayer()
		: Layer("Example")
	{

	}

	~MainLayer()
	{
		delete squar;
		delete shader;
		delete colorShader;
		delete texture;
	}

	void OnAttach() override
	{
		std::vector<Vertex> cubeVertices = {
			// Bottom face
			Vertex{ { -0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},  // 0
			Vertex{ {  0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},  // 1
			Vertex{ {  0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},  // 2
			Vertex{ { -0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},  // 3

			// Top face
			Vertex{ { -0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},  // 4
			Vertex{ {  0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},  // 5
			Vertex{ {  0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},  // 6
			Vertex{ { -0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},  // 7

			// Left face
			Vertex{ { -0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},  // 8
			Vertex{ { -0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},  // 9
			Vertex{ { -0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},  // 10
			Vertex{ { -0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},  // 11

			// Right face
			Vertex{ {  0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},  // 12
			Vertex{ {  0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},  // 13
			Vertex{ {  0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},  // 14
			Vertex{ {  0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},  // 15

			// Front face
			Vertex{ { -0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},  // 16
			Vertex{ {  0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},  // 17
			Vertex{ {  0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},  // 18
			Vertex{ { -0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},  // 19

			// Back face
			Vertex{ { -0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},  // 20
			Vertex{ {  0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},  // 21
			Vertex{ {  0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},  // 22
			Vertex{ { -0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},  // 23

		};


		std::vector<unsigned int> cubeIndices = {
			// Bottom face
			0, 1, 2,   // First triangle
			2, 3, 0,   // Second triangle

			// Top face
			4, 5, 6,   // First triangle
			6, 7, 4,   // Second triangle

			// Left face
			8, 9, 10,  // First triangle
			10, 11, 8, // Second triangle

			// Right face
			12, 13, 14, // First triangle
			14, 15, 12, // Second triangle

			// Front face
			16, 17, 18, // First triangle
			18, 19, 16, // Second triangle

			// Back face
			20, 21, 22, // First triangle
			22, 23, 20  // Second triangle
		};

		squar = new Misk::Mesh(cubeVertices, cubeIndices);
		MK_ASSERT(squar, "the object faild")
			squar->initMesh();

		shader = Misk::CreateShader();
		MK_ASSERT(shader, "the object faild")

		shader->init("src/resource/shaders/shaderV1.vert", "src/resource/shaders/shaderV1.frag");
		unsigned int textureID;
		int width, height, bitDepth;
		unsigned char* texData = stbi_load("src/resource/media/container.jpg", &width, &height, &bitDepth, 0);
		MK_ASSERT(texData, "Failed to load texture");
		MK_TRACE("{0}, {1}", width, height);
		texture = Misk::Texture::CreateTexture();
		texture->loadTexture("src/resource/media/container.jpg");

		colorShader = Misk::CreateShader();
		MK_ASSERT(colorShader, "the shader object faild!");
		colorShader->init("src/resource/shaders/colorObject.vert", "src/resource/shaders/colorObject.frag");
	}

	void OnUpdate(Misk::Timestep ts) override
	{
		static bool mouseOn = false;
		deltaTime = ts;
		Misk::Application& app = Misk::Application::Get();
		
		camera.freeCamera(ts);
		//if (Misk::Input::IsKeyPressed(MK_KEY_C))
		//{
		//	mouseOn = !mouseOn;
		//}
		//if (mouseOn)
		//{
		//	app.GetWindow().MouseOn(false);
		//}
		//else
		//	app.GetWindow().MouseOn(true);

		camera.mouseControl(app.GetXChange(), app.GetYChange());
		glm::mat4 model(1.0f);

		colorShader->use();

		MK_ASSERT(colorShader, "the shader object not iniatilize!");
		colorShader->setMat4f("view", camera.calculateViewMatrix());
		colorShader->setMat4f("projection", projection);
		colorShader->setVec4f("objectColor", glm::vec4(1.0f));
		//!the light source
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.4f));
		colorShader->setMat4f("model", model);
		squar->DrawMesh();
		//XDrawObject(squar, colorShader);


		shader->use();
		shader->setMat4f("view", camera.calculateViewMatrix());
		shader->setMat4f("projection", projection);
		//MK_INFO("ExampleLayer::Update");


		if (angle > 360.0f)
			angle = 0.0f;
		//transformation matrix(model)
		for (int i = 0; i < 5; i++) {

			angle += speedAng * ts;
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(float(tx * i/10), ty, tz));
			model = glm::scale(model, glm::vec3(tempScal));
			model = glm::rotate(model, (angle * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
			shader->setMat4f("model", model);
			texture->applyTexture(0);
			squar->DrawMesh();
			//xDrawObject(squar, shader);
		}

		
	}

	void OnImguiRender() override
	{
		static bool show_another_window = true;
		MK_ASSERT(Misk::ImguiLayer::GetImguiContext(), "sad!");
		ImGui::SetCurrentContext(Misk::ImguiLayer::GetImguiContext());

		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("My name is almakhtar and this my window!");
			ImGui::Text("current angle = %.2f", angle);

			ImGui::SliderFloat("rotate speed", &speedAng, 0.0f, 3.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("scale", &tempScal, -10.0f, 30.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("x", &tx, -10.0f, 60.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("y", &ty, -10.0f, 30.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("z", &tz, -10.0f, 30.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::End();
		}
	}

	void OnEvent(Misk::Event& e) override
	{


	}
	

private:
	Misk::Mesh* squar;
	Misk::Shader* shader;
	Misk::Shader* colorShader;


};



Game::Game()
{
	//! Globel varible initialization
	
	projection = glm::perspective(45.0f,
		(float) this->GetWindow().GetWidth() / (float) this->GetWindow().GetHeight(),
		0.1f, 100.0f);
	camera = Misk::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	PushLayer(new MainLayer());
	
}

Game::~Game()
{
}



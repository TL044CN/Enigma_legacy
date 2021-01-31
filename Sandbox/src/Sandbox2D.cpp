#include "Sandbox2D.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() :Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {

	//MAKE A RECTANGLE

	//	Create new Vertex Array
	m_SquareVA = Enigma::VertexArray::Create();

	//	define Vertices to put into the Vertex Buffer for the Vertex Array
	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	//	Create new Vertex Buffer and define the Memory Layout
	Enigma::Ref<Enigma::VertexBuffer> squareVB;
	squareVB.reset(Enigma::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Enigma::ShaderDataType::Float3, "a_Position" }
	});

	//	add the Vertex Buffer to the Vertex Array
	m_SquareVA->AddVertexBuffer(squareVB);

	//	set up Index Buffer for the rectangle
	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Enigma::Ref<Enigma::IndexBuffer> squareIB;
	squareIB.reset(Enigma::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

	//	set the Index Buffer for the Vertex Array
	m_SquareVA->SetIndexBuffer(squareIB);

	//	create the Shader for the Rectangle
	m_FlatColorShader = Enigma::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach(){}

void Sandbox2D::OnUpdate(Enigma::Timestep t) {
	//Update Camera Controler
	m_CameraController.OnUpdate(t);

	//Render Scene
	//	setup rendering environment
	Enigma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f,1.0f });
	Enigma::RenderCommand::Clear();
	Enigma::Renderer::BeginScene(m_CameraController.GetCamera());

	//	bind shader and upload information to it
	std::dynamic_pointer_cast<Enigma::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Enigma::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	//	load the shader into the Renderer
	Enigma::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//	Flush scene
	Enigma::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	//Set ImGui Window Title
	ImGui::Begin("Settings");
	//add Controlls to change the Square Color
	ImGui::ColorEdit4("SquareColor", glm::value_ptr(m_SquareColor));
	//flush
	ImGui::End();
}

void Sandbox2D::OnEvent(Enigma::Event& e) {
	//just pass on the Event
	m_CameraController.OnEvent(e);
}

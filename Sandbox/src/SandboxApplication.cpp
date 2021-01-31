#include <Enigma.h>
#include <Enigma/EntryPoint.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"

class TestLayer : public Enigma::Layer {
public:
	TestLayer()
	: Layer("Test"), m_CameraController(1280.0f/720.0f) {
		m_SquareVA = Enigma::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Enigma::Ref<Enigma::VertexBuffer> squareVB;
		squareVB.reset(Enigma::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Enigma::ShaderDataType::Float3, "a_Position" },
			{ Enigma::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Enigma::Ref<Enigma::IndexBuffer> squareIB;
		squareIB.reset(Enigma::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		auto flatColorShader = m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

		m_Texture = Enigma::Texture2D::Create("assets/textures/test.png");

		std::dynamic_pointer_cast<Enigma::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Enigma::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Enigma::Timestep ts) override {
		//Update Camera
		m_CameraController.OnUpdate(ts);

		//Begin Rendering
		Enigma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f,1.0f });
		Enigma::RenderCommand::Clear();


		Enigma::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

		auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

		std::dynamic_pointer_cast<Enigma::OpenGLShader>(flatColorShader)->Bind();
		std::dynamic_pointer_cast<Enigma::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		glm::vec3 pos(0.51f, 0.51f, 0.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		Enigma::Renderer::Submit(flatColorShader, m_SquareVA, transform);

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Enigma::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		Enigma::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Enigma::Event& event) override {
		m_CameraController.OnEvent(event);
	}

private:
	Enigma::ShaderLibrary m_ShaderLibrary;

	Enigma::Ref<Enigma::VertexArray> m_VertexArray;
	Enigma::Ref<Enigma::VertexArray> m_SquareVA;

	Enigma::Ref<Enigma::Texture2D> m_Texture;
	Enigma::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Enigma::Application {
public:
	Sandbox() {
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {

	}

};

Enigma::Application* Enigma::CreateApplication() {
	return new Sandbox();
}
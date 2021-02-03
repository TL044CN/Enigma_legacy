#include "Sandbox2D.h"
#include <ImGui/imgui.h>

#include <glm/gtc/type_ptr.hpp>

#include <chrono>

//Create a new Sandbox2D Layer with a 16:9 aspect ratio Camera controller
Sandbox2D::Sandbox2D() :Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

//Initializes the Sandbox Layer
void Sandbox2D::OnAttach() {
	//read the Missing Texture texture.
	m_MissingTexture = Enigma::Texture2D::Create("assets/textures/404.png");
}

//cleanup after the Sandbox Layer is deatached
void Sandbox2D::OnDetach(){}

void Sandbox2D::OnUpdate(Enigma::Timestep t) {
	ENGM_PROFILE_SCOPE("Sandbox2D::OnUpdate");

	//Update Camera Controler
	m_CameraController.OnUpdate(t);

	Enigma::Renderer2D::ResetStats();
	{
		ENGM_PROFILE_SCOPE("Renderer Preparation");

		//Render Scene
		//	setup rendering environment
		Enigma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f,1.0f });
		Enigma::RenderCommand::Clear();
	}
	{
		ENGM_PROFILE_SCOPE("Renderer Draw");
		//Draw Rectangles
		Enigma::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Enigma::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
		Enigma::Renderer2D::DrawRotatedQuad({ 0.5f, 0.5f, 0.1f }, { 1.0f, 1.0f }, 45.0f, m_MissingTexture, 5.0f);

		//	Flush scene
		Enigma::Renderer2D::EndScene();

		//Unbind Framebuffer

		//Test Batchrenderer
		Enigma::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for(float y = -5.0f; y<5.0f; y+=0.5f)
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { 0.0f, ((float)((float)rand() / (float)RAND_MAX) * 0.2f) + 0.6f, 0.2f, 0.9f };
				Enigma::Renderer2D::DrawQuad({ x,y }, { 0.45f,0.45f }, color);
			}
		Enigma::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	ENGM_PROFILE_FUNCTION();

	//Set ImGui Window Title
	ImGui::Begin("Settings");

	//get the Renderer Stats
	auto stats = Enigma::Renderer2D::GetStats();
	//display the Renderer Stats
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("DrawCalls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	//add Controlls to change the Square Color
	ImGui::ColorEdit4("SquareColor", glm::value_ptr(m_SquareColor));

	//End that Part
	ImGui::End();
}

void Sandbox2D::OnEvent(Enigma::Event& e) {
	//just pass on the Event
	m_CameraController.OnEvent(e);
}

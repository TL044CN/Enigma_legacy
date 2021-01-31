#include "Sandbox2D.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() :Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {
	m_MissingTexture = Enigma::Texture2D::Create("assets/textures/404.png");
}

void Sandbox2D::OnDetach(){}

void Sandbox2D::OnUpdate(Enigma::Timestep t) {
	//Update Camera Controler
	m_CameraController.OnUpdate(t);

	//Render Scene
	//	setup rendering environment
	Enigma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f,1.0f });
	Enigma::RenderCommand::Clear();
	Enigma::Renderer2D::BeginScene(m_CameraController.GetCamera());

	//Draw Rectangles
	Enigma::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
	Enigma::Renderer2D::DrawQuad({ 0.5f, 0.5f, 0.1f }, { 1.0f, 1.0f }, m_MissingTexture);

	//	Flush scene
	Enigma::Renderer2D::EndScene();
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

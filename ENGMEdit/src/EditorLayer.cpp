#include "EditorLayer.h"
#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

//Create a new Sandbox2D Layer with a 16:9 aspect ratio Camera controller
EditorLayer::EditorLayer() :Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

//Initializes the Sandbox Layer
void EditorLayer::OnAttach() {
	//read the Missing Texture texture.
	m_MissingTexture = Enigma::Texture2D::Create("assets/textures/404.png");

	//Setup Framebuffer
	Enigma::FramebufferSpecs fb_Specs;
	fb_Specs.Width = 1280;
	fb_Specs.Height = 720;
	m_Framebuffer = Enigma::Framebuffer::Create(fb_Specs);
}

//cleanup after the Sandbox Layer is deatached
void EditorLayer::OnDetach(){
	ENGM_PROFILE_FUNCTION();
}

void EditorLayer::OnUpdate(Enigma::Timestep t) {
	ENGM_PROFILE_FUNCTION();

	//Update Camera Controler
	m_CameraController.OnUpdate(t);

	//Render
	Enigma::Renderer2D::ResetStats();
	{
		ENGM_PROFILE_SCOPE("Renderer Preparation");
		//Bind Framebuffer
		m_Framebuffer->Bind();

		//Render Scene
		//	setup rendering environment
		Enigma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f,1.0f });
		Enigma::RenderCommand::Clear();
	}
	{
		static float rotation = 0.0f;
		rotation += t * 50.0f;

		ENGM_PROFILE_SCOPE("Renderer Draw");
		//Draw Rectangles
		Enigma::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Enigma::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
		Enigma::Renderer2D::DrawRotatedQuad({ 0.5f, 0.5f, 0.1f }, { 1.0f, 1.0f }, rotation, m_MissingTexture, 5.0f);

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
		m_Framebuffer->Unbind();
	}
}

void EditorLayer::OnImGuiRender() {
	ENGM_PROFILE_FUNCTION();

	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen) {
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoNavFocus;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Dockspace", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Exit")) Enigma::Application::Get().Close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

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

	ImGui::End();

	//Viewport Display:
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
	ImGui::Begin("Viewpoort");
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	if (m_ViewportSize != *((glm::vec2*) & viewportPanelSize)) {
		m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
	}

	//get TextureID of the Framebuffer
	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	//Display Texture
	ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

	//End that Part
	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();
}

void EditorLayer::OnEvent(Enigma::Event& e) {
	//just pass on the Event
	m_CameraController.OnEvent(e);
}

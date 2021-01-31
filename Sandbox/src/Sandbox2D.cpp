#include "Sandbox2D.h"
#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

//Timer for Profiling
template<typename Fn>
class Timer {
public:
	//Create a Timepoint and start counting happily
	Timer(const char* name, Fn&& function) :m_Name(name), m_Function(function), m_Stopped(false) {
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	//When leaving Scope or when deleted, stop the timer
	~Timer() {
		if (!m_Stopped)
			Stop();
	}

	//When Stopped call the Callback Function (which will then put the result into a Profiler Struct)
	void Stop() {
		//save the Timepoint when the Timer was stopped
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		//Cast the Timepoints to millisecond values
		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		//calculate the duration from start to end
		float duration = (end - start) * 0.001f;

		//call Callback Function and turn over the results and name of the Timer
		m_Function({ m_Name, duration });
	}
private:
	const char* m_Name;
	Fn m_Function;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

//add the current Scope to the Profiling list (creates a Timer with the specified name, when it goes out of scope it saves the result in a new ProfileResult struct)
#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult){m_ProfileResults.push_back(profileResult); })

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
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		//Update Camera Controler
		m_CameraController.OnUpdate(t);
	}

	{
		PROFILE_SCOPE("Renderer Preparation");
		//Render Scene
		//	setup rendering environment
		Enigma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f,1.0f });
		Enigma::RenderCommand::Clear();
	}
	{
		PROFILE_SCOPE("Renderer Draw");
		//Draw Rectangles
		Enigma::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Enigma::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
		Enigma::Renderer2D::DrawQuad({ 0.5f, 0.5f, 0.1f }, { 1.0f, 1.0f }, m_MissingTexture);

		//	Flush scene
		Enigma::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	//Set ImGui Window Title
	ImGui::Begin("Settings");
	//add Controlls to change the Square Color
	ImGui::ColorEdit4("SquareColor", glm::value_ptr(m_SquareColor));

	//print all the Profiler Results
	for (auto& result : m_ProfileResults) {
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	//clear the Profile Results to not clutter everything with Results
	m_ProfileResults.clear();

	//flush
	ImGui::End();
}

void Sandbox2D::OnEvent(Enigma::Event& e) {
	//just pass on the Event
	m_CameraController.OnEvent(e);
}

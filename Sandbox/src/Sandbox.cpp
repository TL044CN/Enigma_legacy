#include "engmpch.h"
#include <Enigma.h>

#include "imgui/imgui.h"

class TestLayer : public Enigma::Layer {
public:
	TestLayer() : Layer("Test") {}

	void OnUpdate() override {

	}

	virtual void OnImGuiRender() override {
/*		ImGui::Begin("Test");
		ImGui::Text("Test String");
		ImGui::End();
*/	}

	void OnEvent(Enigma::Event& event) override {
		ENGM_TRACE("{0}", event);
	}
};

class Sandbox : public Enigma::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
	}

	~Sandbox() {

	}

};

Enigma::Application* Enigma::CreateApplication() {
	return new Sandbox();
}

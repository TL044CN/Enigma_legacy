#include "engmpch.h"
#include <Enigma.h>


class TestLayer : public Enigma::Layer {
public:
	TestLayer() : Layer("Test") {}

	void OnUpdate() override {

	}

	void OnEvent(Enigma::Event& event) override {
		ENGM_TRACE("{0}", event);
	}
};

class Sandbox : public Enigma::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
		PushOverlay(new Enigma::ImGuiLayer());
	}

	~Sandbox() {

	}

};

Enigma::Application* Enigma::CreateApplication() {
	return new Sandbox();
}

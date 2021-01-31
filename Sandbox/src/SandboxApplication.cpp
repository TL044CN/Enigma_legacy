#include <Enigma.h>
#include <Enigma/Core/EntryPoint.h>
#include <imgui/imgui.h>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"

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
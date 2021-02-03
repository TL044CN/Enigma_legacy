#include <Enigma.h>
#include <Enigma/Core/EntryPoint.h>
#include "EditorLayer.h"

class ENGMEdit : public Enigma::Application {
public:
	ENGMEdit() {
		PushLayer(new EditorLayer());
	}

	~ENGMEdit() {

	}

};

Enigma::Application* Enigma::CreateApplication() {
	return new ENGMEdit();
}
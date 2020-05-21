#include "engmpch.h"
#include <Enigma.h>

class Sandbox : public Enigma::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}

};

Enigma::Application* Enigma::CreateApplication() {

	return new Sandbox();

}

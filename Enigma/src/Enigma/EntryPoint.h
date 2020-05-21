#pragma once

#ifdef ENGM_PLATFORM_WINDOWS

#include <stdio.h>

extern Enigma::Application* Enigma::CreateApplication();

int main(int argc, char** argv) {

	auto app = Enigma::CreateApplication();
	app->Run();
	delete app;

}

#endif

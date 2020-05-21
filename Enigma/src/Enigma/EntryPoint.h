#pragma once

#ifdef ENGM_PLATFORM_WINDOWS

#include <stdio.h>

extern Enigma::Application* Enigma::CreateApplication();

int main(int argc, char** argv) {

	Enigma::Log::Init();
	ENGM_CORE_WARN("Initialized Log");
	ENGM_CLIENT_INFO("Initialized Log");

	auto app = Enigma::CreateApplication();
	app->Run();
	delete app;

}

#endif

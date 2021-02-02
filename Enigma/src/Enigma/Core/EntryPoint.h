#pragma once

#include "Enigma/Core.h"

#ifdef ENGM_PLATFORM_WINDOWS

extern Enigma::Application* Enigma::CreateApplication();

int main(int argc, char** argv) {
	Enigma::Log::Init();
	ENGM_CORE_WARN("Initialized Core Log");
	ENGM_INFO("Initialized Clientside Log");

	ENGM_PROFILE_BEGIN_SESSION("Startup", "EnigmaProfile-Startup.json");
	auto app = Enigma::CreateApplication();
	ENGM_PROFILE_END_SESSION();

	ENGM_PROFILE_BEGIN_SESSION("Startup", "EnigmaProfile-Runtime.json");
	app->Run();
	ENGM_PROFILE_END_SESSION();

	ENGM_PROFILE_BEGIN_SESSION("Startup", "EnigmaProfile-Shutdown.json");
	delete app;
	ENGM_PROFILE_END_SESSION();

}

#endif

#pragma once

#ifdef ENGM_PLATFORM_WINDOWS

extern Enigma::Application* Enigma::CreateApplication();

int main(int argc, char** argv) {

	Enigma::Log::Init();
	ENGM_CORE_WARN("Initialized Core Log");
	ENGM_CLIENT_INFO("Initialized Clientside Log");

	auto app = Enigma::CreateApplication();
	app->Run();
	delete app;

}

#endif

#pragma once
#include "Core.h"

namespace Enigma {

	class ENIGMA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//to be defined by the Client Application
	Application* CreateApplication();

}

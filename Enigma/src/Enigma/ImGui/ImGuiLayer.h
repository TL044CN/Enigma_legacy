#pragma once
#include "Enigma/Layer.h"

#include "Enigma/Events/KeyEvent.h"
#include "Enigma/Events/MouseEvent.h"
#include "Enigma/Events/ApplicationEvent.h"

namespace Enigma {

	class ENIGMA_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}

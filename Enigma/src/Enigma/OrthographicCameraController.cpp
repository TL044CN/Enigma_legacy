#include "engmpch.h"
#include "OrthographicCameraController.h"

#include "Enigma/Input.h"
#include "Enigma/Core/Keycodes.h"

namespace Enigma {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
	:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio*m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) { }

	void OrthographicCameraController::OnUpdate(Timestep t) {
		if (Input::IsKeyPressed(ENGM_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * t;
		else if (Input::IsKeyPressed(ENGM_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * t;

		if (Input::IsKeyPressed(ENGM_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * t;
		else if (Input::IsKeyPressed(ENGM_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * t;

		if (m_Rotation) {
			if (Input::IsKeyPressed(ENGM_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * t;
			else if (Input::IsKeyPressed(ENGM_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * t;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ENGM_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ENGM_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		m_ZoomLevel -= e.GetYOffset() * .25f;
		m_ZoomLevel = std::max(m_ZoomLevel, .25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
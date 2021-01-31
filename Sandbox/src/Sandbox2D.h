#pragma once

#include "Enigma.h"

class Sandbox2D : public Enigma::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Enigma::Timestep t) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Enigma::Event& e) override;

private:
	Enigma::OrthographicCameraController m_CameraController;

	Enigma::Ref<Enigma::VertexArray> m_SquareVA;
	Enigma::Ref<Enigma::Shader> m_FlatColorShader;

	Enigma::Ref<Enigma::Texture2D> m_MissingTexture;

	glm::vec4 m_SquareColor = { 0.8f, 0.5f, 0.3f, 1.0f };
};
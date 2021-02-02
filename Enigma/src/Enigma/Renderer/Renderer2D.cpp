#include "engmpch.h"
#include "Enigma/Renderer/Renderer2D.h"

#include "Enigma/Renderer/VertexArray.h"
#include "Enigma/Renderer/Shader.h"
#include "Enigma/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Enigma {

	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {
		ENGM_PROFILE_FUNCTION();

		//Creating a Storage and Vertex Array
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		//Defining a Quad (vertices and texture coordinates)
		// x,y,z	,	u,v
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
		};

		//Creating a Vertex Buffer for the Vertex Array and setting up its Mamorylayout
		Ref<VertexBuffer> squareVertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});

		//Add Vertex Buffer to the Vertex Array
		s_Data->QuadVertexArray->AddVertexBuffer(squareVertexBuffer);

		//	set up Index Buffer for the Quad
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Enigma::Ref<Enigma::IndexBuffer> squareIndexBuffer = Enigma::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		//	set the Index Buffer for the Vertex Array
		s_Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);

		//	create the Shaders for the Quad
		//    Create White Texture
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		//    Create Texture from File
		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");

		//  Bind Texture Shader
		s_Data->TextureShader->Bind();
		//  Set the Texture
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown() {
		ENGM_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {		
		ENGM_PROFILE_FUNCTION();

		//Binding Texture Shader
		s_Data->TextureShader->Bind();
		//Setting View Projection Matrix of the Texture Shader
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene() {
		ENGM_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		//convert vec2 to vec3 and call the other DrawQuad function
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		ENGM_PROFILE_FUNCTION();

		//upload Color of the Quad to the Shader
		s_Data->TextureShader->SetFloat4("u_Color", color);
		//upload Tiling Factor
		s_Data->TextureShader->SetFloat("u_FilingFactor", 1.0f);
		//Bind WhiteTexture to Shader
		s_Data->WhiteTexture->Bind();

		//apply Transform to the Quad (position and scale)
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		//Bind Vertex Array to the Shader to define a quad then draw the Quad
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		//convert vec2 to vec3 and call the other DrawQuad function
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		ENGM_PROFILE_FUNCTION();

		//Set Tintcolor and Tiling Factor
		s_Data->TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);

		//Bind Shader to the Quad and Texture to Shader
		s_Data->TextureShader->Bind();
		texture->Bind();
		
		//apply Transform to the Quad (position and size)
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		//Bind Vertex Array to the shader to define the Quad draw
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
		ENGM_PROFILE_FUNCTION();

		//set Color of Quad and set the Tiling Factor to 1
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TilingFactor", 1.0f);

		//Bind WhiteTexture
		s_Data->WhiteTexture->Bind();

		//set Transform
		glm::mat4 transform =	glm::translate(glm::mat4(1.0f), position) *
								glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
								glm::scale(glm::mat4(1.0f), { size.x, size.y, 10.f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		//Bind VertexArray
		s_Data->QuadVertexArray->Bind();

		//Draw Quad
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		ENGM_PROFILE_FUNCTION();

		//set Color of Quad and set the Tiling Factor to 1, then Bind Texture
		s_Data->TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();
		
		//set Transform
		glm::mat4 transform =	glm::translate(glm::mat4(1.0f), position) *
								glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
								glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		//Bind Vertex Array
		s_Data->QuadVertexArray->Bind();

		//Draw Quad
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}

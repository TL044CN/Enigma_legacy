#include "engmpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Enigma {

	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
		Ref<Shader> TextureShader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {
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
		Ref<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});

		//Add Vertex Buffer to the Vertex Array
		s_Data->QuadVertexArray->AddVertexBuffer(squareVertexBuffer);

		//	set up Index Buffer for the Quad
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Enigma::Ref<Enigma::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Enigma::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		//	set the Index Buffer for the Vertex Array
		s_Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);

		//	create the Shaders for the Quad
		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");

		//  Bind Texture Shader
		s_Data->TextureShader->Bind();
		//  Set the Texture
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown() {
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		//Binding FlatColorShader
		s_Data->FlatColorShader->Bind();
		//Setting the View Projection Matrix of the FlatColorShader
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		
		//Binding Texture Shader
		s_Data->TextureShader->Bind();
		//Setting View Projection Matrix of the Texture Shader
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene(){}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		//convert vec2 to vec3 and call the other DrawQuad function
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		//Bind Flat Color Shader to the Quad
		s_Data->FlatColorShader->Bind();
		//upload Color of the Quad to the Shader
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		//apply Transform to the Quad (position and scale)
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);

		//Bind Vertex Array to the Shader to define a quad then draw the Quad
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture){
		//convert vec2 to vec3 and call the other DrawQuad function
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
		//Bind Texture Shader to the Quad
		s_Data->TextureShader->Bind();
		
		//apply Transform to the Quad (position and size)
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		//Bind texture and Vertex Array to the shader to define the Quad draw
		texture->Bind();
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}

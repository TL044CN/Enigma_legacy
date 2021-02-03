#include "engmpch.h"
#include "Enigma/Renderer/Renderer2D.h"

#include "Enigma/Renderer/VertexArray.h"
#include "Enigma/Renderer/Shader.h"
#include "Enigma/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Enigma {

	//Quad Vertex.. Defines a Quad
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData {
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;	//0 = White Texture / Flat Color

		glm::vec4 QuadVertexPosition[4];
		glm::vec2 QuadTexIndex[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init() {
		ENGM_PROFILE_FUNCTION();

		//Creating a Storage and Vertex Array
		s_Data.QuadVertexArray = VertexArray::Create();

		//Creating a Vertex Buffer for the Vertex Array and setting up it's Mamorylayout
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"},
			{ShaderDataType::Float, "a_TexIndex"},
			{ShaderDataType::Float, "a_TilingFactor"}
		});

		//Add Vertex Buffer to the Vertex Array
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		//Create the Buffer Base
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		//set up index Buffer
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}

		//Create Quad Indexbuffer and cleanup
		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
		delete[] quadIndices;

		//	create the Shaders for the Quad
		//    Create White Texture
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		//Set up Texture Sampler
		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		//    Create Texture from File
		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");

		//  Bind Texture Shader
		s_Data.TextureShader->Bind();
		//  Set the Textures
		s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);
		//  Set texture slot 0 to white texture
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		//Setup QuadVertexPosition
		s_Data.QuadVertexPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

		//Setup QuadTexIndex
		s_Data.QuadTexIndex[0] = { 0.0f, 0.0f };
		s_Data.QuadTexIndex[1] = { 1.0f, 0.0f };
		s_Data.QuadTexIndex[2] = { 1.0f, 1.0f };
		s_Data.QuadTexIndex[3] = { 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown() {
		ENGM_PROFILE_FUNCTION();

		//reset Quad Index Count and Pointer
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		//reset Texture Slot to the first Slot (0 is flat color)
		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {		
		ENGM_PROFILE_FUNCTION();

		//Binding Texture Shader
		s_Data.TextureShader->Bind();
		//Setting View Projection Matrix of the Texture Shader
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		//Initialize Constants
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		//Start at index 1, 0 would be flat color
		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene() {
		ENGM_PROFILE_FUNCTION();

		//update Data Size
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		//set Vertex Buffer Data
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		//Flush Renderer
		Flush();
	}

	void Renderer2D::Flush() {
		//Bind Textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		//now draw all the Quads in Batches
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

		//Update Stats
		s_Data.Stats.DrawCalls++;
	}

	//Used when the Maximum Quadcount for a single Batchrendering Process is exceded
	void Renderer2D::FlushAndReset() {
		//First end the Scene as usual
		EndScene();

		//reset all the Counts to their base values
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		//convert vec2 to vec3 and call the other DrawQuad function
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		ENGM_PROFILE_FUNCTION();

		//If the maximum Render Count of a single Batch is exceded, Flush and continue with a new Batch
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		const float textureIndex = 0.0f;
		const float tilingFactor = 1.0f;

		//Build VertexBuffer
		//	Setup Transform Matrix
		glm::mat4 transform =	glm::translate(glm::mat4(1.0f), position) *
								glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		//  Setup Vertices
		for (uint8_t VertexIndex = 0; VertexIndex < 4; VertexIndex++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[VertexIndex];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = s_Data.QuadTexIndex[VertexIndex];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;

		//update Stats
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor){
		//convert vec2 to vec3 and call the other DrawQuad function
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		ENGM_PROFILE_FUNCTION();

		//If the maximum Render Count of a single Batch is exceded, Flush and continue with a new Batch
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		//check if the texture was already added to the texture buffer before
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		//if the texture has not yet been added to the texture buffer add it
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		//Build VertexBuffer
		//	Setup Transform Matrix
		glm::mat4 transform =	glm::translate(glm::mat4(1.0f), position) *
								glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		//  Setup Vertices
		for (uint8_t VertexIndex = 0; VertexIndex < 4; VertexIndex++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[VertexIndex];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = s_Data.QuadTexIndex[VertexIndex];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;

		//update Stats
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
		ENGM_PROFILE_FUNCTION();

		//If the maximum Render Count of a single Batch is exceded, Flush and continue with a new Batch
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		//No Texture (uniform White and some Tiling Factor which doesnt really matter)
		const float textureIndex = 0.0f;
		const float tilingFactor = 1.0f;

		//set Transform
		glm::mat4 transform =	glm::translate(glm::mat4(1.0f), position) *
								glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
								glm::scale(glm::mat4(1.0f), { size.x, size.y, 10.f });

		//  Setup Vertices
		for (uint8_t VertexIndex = 0; VertexIndex < 4; VertexIndex++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[VertexIndex];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = s_Data.QuadTexIndex[VertexIndex];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;

		//update Stats
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		ENGM_PROFILE_FUNCTION();

		//If the maximum Render Count of a single Batch is exceded, Flush and continue with a new Batch
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		//initialize Texture to flat Color
		float textureIndex = 0.0f;

		//search for the correct Texture
		for(uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}

		//check if the texture was not found in the Texture Slots. then set a new TextureIndex for a new Texture
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		//set Transform
		glm::mat4 transform =	glm::translate(glm::mat4(1.0f), position) *
								glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
								glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		//  Setup Vertices
		for (uint8_t VertexIndex = 0; VertexIndex < 4; VertexIndex++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[VertexIndex];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = s_Data.QuadTexIndex[VertexIndex];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;

		//update Stats
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::ResetStats() {
		//sets everything in the Stats struct to 0
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats() {
		return s_Data.Stats;
	}

}

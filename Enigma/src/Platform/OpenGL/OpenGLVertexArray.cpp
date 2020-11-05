#include "engmpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Enigma {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Enigma::ShaderDataType::Float:    return GL_FLOAT;
		case Enigma::ShaderDataType::Float2:   return GL_FLOAT;
		case Enigma::ShaderDataType::Float3:   return GL_FLOAT;
		case Enigma::ShaderDataType::Float4:   return GL_FLOAT;
		case Enigma::ShaderDataType::Mat3:     return GL_FLOAT;
		case Enigma::ShaderDataType::Mat4:     return GL_FLOAT;
		case Enigma::ShaderDataType::Int:      return GL_INT;
		case Enigma::ShaderDataType::Int2:     return GL_INT;
		case Enigma::ShaderDataType::Int3:     return GL_INT;
		case Enigma::ShaderDataType::Int4:     return GL_INT;
		case Enigma::ShaderDataType::Bool:     return GL_BOOL;
		}

		ENGM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		ENGM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no Layout");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(
				m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			m_VertexBufferIndex++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}
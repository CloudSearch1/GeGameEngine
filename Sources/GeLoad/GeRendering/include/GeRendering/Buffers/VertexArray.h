#pragma once

#include "GeRendering/Buffers/VertexBuffer.h"

namespace GeRendering::Buffers
{
	enum class EType
	{
		BYTE			          = 0x1400,
		UNISGNED_BYTE	      = 0x1401,
		SHORT			          = 0x1402,
		UNSIGNED_SHORT      = 0x1403,
		INT				          = 0x1404,
		UNSIGNED_INT	      = 0x1405,
		FLOAT			          = 0x1406,
		DOUBLE			        = 0x140A
	};

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		template <class T>
		void BindAttribute(uint32_t p_attribute, VertexBuffer<T>& p_vertexBuffer, EType p_type, uint64_t p_count, uint64_t p_stride, intptr_t p_offset);

		void Bind();
		void Unbind();
		//返回VAOID
		GLint GetID();

	private:
		GLuint m_bufferID;
	};
}

#include "GeRendering/Buffers/VertexArray.inl"

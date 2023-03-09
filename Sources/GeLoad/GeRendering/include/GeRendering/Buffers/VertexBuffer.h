#pragma once

#include <vector>

#include "GeRendering/Context/Driver.h"

namespace GeRendering::Buffers
{
	template <class T>
	class VertexBuffer
	{
	public:
		//用缓冲区指针和定点数来创建VBO
		VertexBuffer(T* p_data, size_t p_elements);
		//用vector来创建VBO
		VertexBuffer(std::vector<T>& p_data);
		~VertexBuffer();

		void Bind();
		void Unbind();

		uint32_t GetID();
	private:
		uint32_t m_bufferID;
	};
}

#include "GeRendering/Buffers/VertexBuffer.inl"

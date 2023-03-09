#pragma once

#include <vector>

#include "GeRendering/Context/Driver.h"

namespace GeRendering::Buffers
{
	class IndexBuffer
	{
	public:
    //构建EBO，用index指针和indexcount来构建
		IndexBuffer(unsigned int* p_data, size_t p_elements);
    //用vector来构建EBO
		IndexBuffer(std::vector<uint32_t>& p_data);
		~IndexBuffer();

		void Bind();
		void Unbind();
    //返回EBO的ID
		uint32_t GetID();
	private:
		uint32_t m_bufferID;
	};
}

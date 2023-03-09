#pragma once

#include <vector>

#include "GeRendering/Context/Driver.h"
#include "GeRendering/Buffers/AccessSpecifier.h"

namespace GeRendering::Resources { class Shader; }

namespace GeRendering::Buffers
{
	class ShaderStorageBuffer
	{
	public:
    //根据访问提示符来创建SSBO
		ShaderStorageBuffer(AccessSpecifier p_accessSpecifier);
		~ShaderStorageBuffer();

    //根据给定的bindingpoint绑定SSBO
		void Bind(uint32_t p_bindingPoint);
    //解绑SSBO，根据上一个bindingpoint
		void Unbind();

		//发送数据块
		template<typename T>
		void SendBlocks(T* p_data, size_t p_size);

	private:
		uint32_t m_bufferID;
		uint32_t m_bindingPoint = 0;
	};
}

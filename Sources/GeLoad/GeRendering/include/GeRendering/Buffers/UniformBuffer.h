#pragma once

#include <vector>
#include <string>

#include "GeRendering/Context/Driver.h"
#include "GeRendering/Buffers/EAccessSpecifier.h"

namespace GeRendering::Resources { class Shader; }

namespace GeRendering::Buffers
{
	class UniformBuffer
	{
	public:
		/**
		* 创建UniformBuffer
		* @param p_size 指定UBO的数据字节大小
		* @param p_bindingPoint 指定UBO要绑定的绑定点
		* @parma p_offset UBO的偏移量,等于UBO的大小(如果size不为0)
		* @param p_accessSpecifier
		*/
		UniformBuffer(size_t p_size, uint32_t p_bindingPoint = 0, uint32_t p_offset = 0, EAccessSpecifier p_accessSpecifier = EAccessSpecifier::DYNAMIC_DRAW);
		~UniformBuffer();
		void Bind();
		void Unbind();

    //将 UBO 中位于 p_offset 的数据设置为 p_data
		template<typename T>
		void SetSubData(const T& p_data, size_t p_offset);

		/**
		* 将 UBO 中位于 p_offset 的数据设置为 p_data
		* @param p_data
		* @param p_offsetInOut 将跟踪数据布局的当前步幅
		*/
		template<typename T>
		void SetSubData(const T& p_data, std::reference_wrapper<size_t> p_offsetInOut);
    //返回UBO的ID
		uint32_t GetID() const;
    //绑定一个给定ID的块，将其绑定到给定的Shader上
		static void BindBlockToShader(GeRendering::Resources::Shader& p_shader, uint32_t p_uniformBlockLocation, uint32_t p_bindingPoint = 0);
    //绑定一个给定Name的块，将其绑定到给定的Shader上
		static void BindBlockToShader(GeRendering::Resources::Shader& p_shader, const std::string& p_name, uint32_t p_bindingPoint = 0);
    //返回这指定块的索引，此处用作块的ID
		static uint32_t GetBlockLocation(GeRendering::Resources::Shader& p_shader, const std::string& p_name);
	private:
		uint32_t m_bufferID;
	};
}

#include "GeRendering/Buffers/UniformBuffer.inl"

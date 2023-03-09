#pragma once

#include <vector>

#include "GeRendering/Context/Driver.h"

namespace GeRendering::Buffers
{
	class Framebuffer
	{
	public:
    //采用纹理图片大小来构建famebuffer对象
		Framebuffer(uint16_t p_width = 0, uint16_t p_height = 0);
		~Framebuffer();
    //绑定framebuffer，用最近的framebuffer对象的id
		void Bind();
    //解绑framebuffer，用最近的framebuffer对象的id
		void Unbind();
    //重定义famebuffer对象的大小，用picture的width和height
		void Resize(uint16_t p_width, uint16_t p_height);

    //返回framebufferID,m_bufferID
		uint32_t GetID();
    //返回当前texture的TextureID
		uint32_t GetTextureID();
    //返回m_depthStencilBuffer，the ID of the OpenGL render buffer
		uint32_t GetRenderBufferID();

	private:
		uint32_t m_bufferID = 0;
		uint32_t m_renderTexture = 0;
		uint32_t m_depthStencilBuffer = 0;
	};
}

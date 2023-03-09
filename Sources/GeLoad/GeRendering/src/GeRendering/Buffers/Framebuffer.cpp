#include <GL/glew.h>

#include "GeRendering/Buffers/Framebuffer.h"

GeRendering::Buffers::Framebuffer::Framebuffer(uint16_t p_width, uint16_t p_height)
{
  //生成对象
	glGenFramebuffers(1, &m_bufferID);
	glGenTextures(1, &m_renderTexture);
	glGenRenderbuffers(1, &m_depthStencilBuffer);

  //设置纹理
	glBindTexture(GL_TEXTURE_2D, m_renderTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

  //设置framebuffer
	Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderTexture, 0);
	Unbind();

	Resize(p_width, p_height);
}

GeRendering::Buffers::Framebuffer::~Framebuffer()
{
  glDeleteBuffers(1, &m_bufferID);
	glDeleteTextures(1, &m_renderTexture);
	glDeleteRenderbuffers(1, &m_depthStencilBuffer);
}

void GeRendering::Buffers::Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);
}

void GeRendering::Buffers::Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GeRendering::Buffers::Framebuffer::Resize(uint16_t p_width, uint16_t p_height)
{
  //resize 纹理
	glBindTexture(GL_TEXTURE_2D, m_renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_width, p_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

  //设置深度模板缓冲区
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, p_width, p_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

  //将深度和模板缓冲区附着到framebuffer
	Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBuffer);
	Unbind();
}

uint32_t GeRendering::Buffers::Framebuffer::GetID()
{
	return m_bufferID;
}

uint32_t GeRendering::Buffers::Framebuffer::GetTextureID()
{
	return m_renderTexture;
}

uint32_t GeRendering::Buffers::Framebuffer::GetRenderBufferID()
{
	return m_depthStencilBuffer;
}

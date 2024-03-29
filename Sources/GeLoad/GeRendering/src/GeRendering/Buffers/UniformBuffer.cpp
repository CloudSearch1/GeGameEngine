/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <GL/glew.h>

#include "GeRendering/Buffers/UniformBuffer.h"
#include "GeRendering/Resources/Shader.h"

GeRendering::Buffers::UniformBuffer::UniformBuffer(size_t p_size, uint32_t p_bindingPoint, uint32_t p_offset, EAccessSpecifier p_accessSpecifier)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	glBufferData(GL_UNIFORM_BUFFER, p_size, NULL, static_cast<GLint>(p_accessSpecifier));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, p_bindingPoint, m_bufferID, p_offset, p_size);
}

GeRendering::Buffers::UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void GeRendering::Buffers::UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
}

void GeRendering::Buffers::UniformBuffer::Unbind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint GeRendering::Buffers::UniformBuffer::GetID() const
{
	return m_bufferID;
}

void GeRendering::Buffers::UniformBuffer::BindBlockToShader(GeRendering::Resources::Shader& p_shader, uint32_t p_uniformBlockLocation, uint32_t p_bindingPoint)
{
	glUniformBlockBinding(p_shader.id, p_uniformBlockLocation, p_bindingPoint);
}

void GeRendering::Buffers::UniformBuffer::BindBlockToShader(GeRendering::Resources::Shader& p_shader, const std::string& p_name, uint32_t p_bindingPoint)
{
	glUniformBlockBinding(p_shader.id, GetBlockLocation(p_shader, p_name), p_bindingPoint);
}

uint32_t GeRendering::Buffers::UniformBuffer::GetBlockLocation(GeRendering::Resources::Shader& p_shader, const std::string& p_name)
{
	return glGetUniformBlockIndex(p_shader.id, p_name.c_str());
}

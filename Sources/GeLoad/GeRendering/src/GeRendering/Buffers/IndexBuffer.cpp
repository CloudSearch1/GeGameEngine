#include <GL/glew.h>

#include "GeRendering/Buffers/IndexBuffer.h"

GeRendering::Buffers::IndexBuffer::IndexBuffer(unsigned int* p_data, size_t p_elements)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_elements * sizeof(unsigned int), p_data, GL_STATIC_DRAW);
}

GeRendering::Buffers::IndexBuffer::IndexBuffer(std::vector<uint32_t>& p_data)
  : IndexBuffer(p_data.data(), p_data.size())
{
}

GeRendering::Buffers::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void GeRendering::Buffers::IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void GeRendering::Buffers::IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t GeRendering::Buffers::IndexBuffer::GetID()
{
	return m_bufferID;
}

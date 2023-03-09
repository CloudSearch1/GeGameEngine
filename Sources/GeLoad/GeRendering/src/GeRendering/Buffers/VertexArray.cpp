/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeRendering/Buffers/VertexArray.h"

GeRendering::Buffers::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_bufferID);
	glBindVertexArray(m_bufferID);
}

GeRendering::Buffers::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_bufferID);
}

void GeRendering::Buffers::VertexArray::Bind()
{
	glBindVertexArray(m_bufferID);
}

void GeRendering::Buffers::VertexArray::Unbind()
{
	glBindVertexArray(0);
}

GLint GeRendering::Buffers::VertexArray::GetID()
{
	return m_bufferID;
}

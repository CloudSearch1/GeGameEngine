#include "GeRendering/Buffers/VertexArray.h"

namespace GeRendering::Buffers
{

  VertexArray::VertexArray()
  {
    glGenVertexArrays(1, &m_bufferID);
    glBindVertexArray(m_bufferID);
  }

  VertexArray::~VertexArray()
  {
    glDeleteVertexArrays(1, &m_bufferID);
  }

  void VertexArray::Bind()
  {
    glBindVertexArray(m_bufferID);
  }

  void VertexArray::Unbind()
  {
    glBindVertexArray(0);
  }

  GLint VertexArray::GetID()
  {
    return m_bufferID;
  }

  template <class T>
  inline void VertexArray::BindAttribute(uint32_t p_attribute, VertexBuffer<T>& p_vertexBuffer, EType p_type, uint64_t p_count, uint64_t p_stride, intptr_t p_offset)
  {
    Bind();
    p_vertexBuffer.Bind();
    glEnableVertexAttribArray(p_attribute);//Enable or disable a generic vertex attribute array
    glVertexAttribPointer(static_cast<GLuint>(p_attribute), static_cast<GLint>(p_count), static_cast<GLenum>(p_type), GL_FALSE, static_cast<GLsizei>(p_stride), reinterpret_cast<const GLvoid*>(p_offset));
  }
}

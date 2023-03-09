#include <GL/glew.h>

#include "GeRendering/Buffers/ShaderStorageBuffer.h"
namespace GeRendering::Buffers
{

  ShaderStorageBuffer::ShaderStorageBuffer(AccessSpecifier p_accessSpecifier)
  {
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bufferID);
    //GL_SHADER_STORAGE_BUFFER -- Read-write storage for shaders
    glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, static_cast<GLenum>(p_accessSpecifier));
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_bufferID);
  }

  ShaderStorageBuffer::~ShaderStorageBuffer()
  {
    glDeleteBuffers(1, &m_bufferID);
  }

  void ShaderStorageBuffer::Bind(uint32_t p_bindingPoint)
  {
    m_bindingPoint = p_bindingPoint;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, p_bindingPoint, m_bufferID);
  }

  void ShaderStorageBuffer::Unbind()
  {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bindingPoint, 0);
  }

  template<typename T>
  void ShaderStorageBuffer::SendBlocks(T* p_data, size_t p_size)
  {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bufferID);
    glBufferData(GL_SHADER_STORAGE_BUFFER, p_size, p_data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  }

}

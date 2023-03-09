#include <GL/glew.h>

#include "GeRendering/Buffers/UniformBuffer.h"
#include "GeRendering/Resources/Shader.h"

namespace GeRendering::Buffers
{

  UniformBuffer::UniformBuffer(size_t p_size, uint32_t p_bindingPoint, uint32_t p_offset, AccessSpecifier p_accessSpecifier)
  {
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
    glBufferData(GL_UNIFORM_BUFFER, p_size, NULL, static_cast<GLint>(p_accessSpecifier));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, p_bindingPoint, m_bufferID, p_offset, p_size);
  }

  UniformBuffer::~UniformBuffer()
  {
    glDeleteBuffers(1, &m_bufferID);
  }

  void UniformBuffer::Bind()
  {
    glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
  }

  void UniformBuffer::Unbind()
  {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  GLuint UniformBuffer::GetID() const
  {
    return m_bufferID;
  }

  void UniformBuffer::BindBlockToShader(GeRendering::Resources::Shader& p_shader, uint32_t p_uniformBlockLocation, uint32_t p_bindingPoint)
  {
    glUniformBlockBinding(p_shader.id, p_uniformBlockLocation, p_bindingPoint);
  }

  void UniformBuffer::BindBlockToShader(GeRendering::Resources::Shader& p_shader, const std::string& p_name, uint32_t p_bindingPoint)
  {
    glUniformBlockBinding(p_shader.id, GetBlockLocation(p_shader, p_name), p_bindingPoint);
  }

  uint32_t UniformBuffer::GetBlockLocation(GeRendering::Resources::Shader& p_shader, const std::string& p_name)
  {
    return glGetUniformBlockIndex(p_shader.id, p_name.c_str());
  }

  template<typename T>
  void UniformBuffer::SetSubData(const T& p_data, size_t p_offsetInOut)
  {
    Bind();
    glBufferSubData(GL_UNIFORM_BUFFER, p_offsetInOut, sizeof(T), std::addressof(p_data));
    Unbind();
  }

  template<typename T>
  void UniformBuffer::SetSubData(const T& p_data, std::reference_wrapper<size_t> p_offsetInOut)
  {
    Bind();
    size_t dataSize = sizeof(T);
    glBufferSubData(GL_UNIFORM_BUFFER, p_offsetInOut.get(), dataSize, std::addressof(p_data));
    p_offsetInOut.get() += dataSize;
    Unbind();
  }
}

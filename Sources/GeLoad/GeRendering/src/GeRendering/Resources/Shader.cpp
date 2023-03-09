#include <GL/glew.h>

//#include <GeDebug/Logger.h>

#include "GeRendering/Resources/Texture.h"
#include "GeRendering/Resources/Shader.h"

GeRendering::Resources::Shader::Shader(const std::string p_path, uint32_t p_id) : path(p_path), id(p_id)
{
	QueryUniforms();
}

GeRendering::Resources::Shader::~Shader()
{
	glDeleteProgram(id);
}

void GeRendering::Resources::Shader::Bind() const
{
	glUseProgram(id);
}

void GeRendering::Resources::Shader::Unbind() const
{
	glUseProgram(0);
}

void GeRendering::Resources::Shader::SetUniformInt(const std::string& p_name, int p_value)
{
	glUniform1i(GetUniformLocation(p_name), p_value);
}

void GeRendering::Resources::Shader::SetUniformFloat(const std::string& p_name, float p_value)
{
	glUniform1f(GetUniformLocation(p_name), p_value);
}

void GeRendering::Resources::Shader::SetUniformVec2(const std::string & p_name, const GeMaths::FVector2 & p_vec2)
{
	glUniform2f(GetUniformLocation(p_name), p_vec2.x, p_vec2.y);
}

void GeRendering::Resources::Shader::SetUniformVec3(const std::string& p_name, const GeMaths::FVector3& p_vec3)
{
	glUniform3f(GetUniformLocation(p_name), p_vec3.x, p_vec3.y, p_vec3.z);
}

void GeRendering::Resources::Shader::SetUniformVec4(const std::string& p_name, const GeMaths::FVector4& p_vec4)
{
	glUniform4f(GetUniformLocation(p_name), p_vec4.x, p_vec4.y, p_vec4.z, p_vec4.w);
}

void GeRendering::Resources::Shader::SetUniformMat4(const std::string& p_name, const GeMaths::FMatrix4& p_mat4)
{
	glUniformMatrix4fv(GetUniformLocation(p_name), 1, GL_TRUE, &p_mat4.data[0]);
}

int GeRendering::Resources::Shader::GetUniformInt(const std::string& p_name)
{
	int value;
	glGetUniformiv(id, GetUniformLocation(p_name), &value);
	return value;
}

float GeRendering::Resources::Shader::GetUniformFloat(const std::string& p_name)
{
	float value;
	glGetUniformfv(id, GetUniformLocation(p_name), &value);
	return value;
}

GeMaths::FVector2 GeRendering::Resources::Shader::GetUniformVec2(const std::string& p_name)
{
	GLfloat values[2];
	glGetUniformfv(id, GetUniformLocation(p_name), values);
	return reinterpret_cast<GeMaths::FVector2&>(values);
}

GeMaths::FVector3 GeRendering::Resources::Shader::GetUniformVec3(const std::string& p_name)
{
	GLfloat values[3];
	glGetUniformfv(id, GetUniformLocation(p_name), values);
	return reinterpret_cast<GeMaths::FVector3&>(values);
}

GeMaths::FVector4 GeRendering::Resources::Shader::GetUniformVec4(const std::string& p_name)
{
	GLfloat values[4];
	glGetUniformfv(id, GetUniformLocation(p_name), values);
	return reinterpret_cast<GeMaths::FVector4&>(values);
}

GeMaths::FMatrix4 GeRendering::Resources::Shader::GetUniformMat4(const std::string& p_name)
{
	GLfloat values[16];
	glGetUniformfv(id, GetUniformLocation(p_name), values);
	return reinterpret_cast<GeMaths::FMatrix4&>(values);
}

bool GeRendering::Resources::Shader::IsEngineUBOMember(const std::string & p_uniformName)
{
	return p_uniformName.rfind("ubo_", 0) == 0;
}

uint32_t GeRendering::Resources::Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache.at(name);

	const int location = glGetUniformLocation(id, name.c_str());

	/*if (location == -1)
		OVLOG_WARNING("Uniform: '" + name + "' doesn't exist");*/

	m_uniformLocationCache[name] = location;

	return location;
}

void GeRendering::Resources::Shader::QueryUniforms()
{
	GLint numActiveUniforms = 0;
	uniforms.clear();
	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
	std::vector<GLchar> nameData(256);
	for (int unif = 0; unif < numActiveUniforms; ++unif)
	{
		GLint arraySize = 0;
		GLenum type = 0;
		GLsizei actualLength = 0;
		glGetActiveUniform(id, unif, static_cast<GLsizei>(nameData.size()), &actualLength, &arraySize, &type, &nameData[0]);
		std::string name(static_cast<char*>(nameData.data()), actualLength);

		if (!IsEngineUBOMember(name))
		{
			std::any defaultValue;

			switch (static_cast<UniformType>(type))
			{
			case GeRendering::Resources::UniformType::UNIFORM_BOOL:			defaultValue = std::make_any<bool>(GetUniformInt(name));					break;
			case GeRendering::Resources::UniformType::UNIFORM_INT:			defaultValue = std::make_any<int>(GetUniformInt(name));						break;
			case GeRendering::Resources::UniformType::UNIFORM_FLOAT:		defaultValue = std::make_any<float>(GetUniformFloat(name));					break;
			case GeRendering::Resources::UniformType::UNIFORM_FLOAT_VEC2:	defaultValue = std::make_any<GeMaths::FVector2>(GetUniformVec2(name));		break;
			case GeRendering::Resources::UniformType::UNIFORM_FLOAT_VEC3:	defaultValue = std::make_any<GeMaths::FVector3>(GetUniformVec3(name));		break;
			case GeRendering::Resources::UniformType::UNIFORM_FLOAT_VEC4:	defaultValue = std::make_any<GeMaths::FVector4>(GetUniformVec4(name));		break;
			case GeRendering::Resources::UniformType::UNIFORM_SAMPLER_2D:	defaultValue = std::make_any<GeRendering::Resources::Texture*>(nullptr);	break;
			}

			if (defaultValue.has_value())
			{
				uniforms.push_back
				({
					static_cast<UniformType>(type),
					name,
					GetUniformLocation(nameData.data()),
					defaultValue
				});
			}
		}
	}
}

const GeRendering::Resources::UniformInfo* GeRendering::Resources::Shader::GetUniformInfo(const std::string& p_name) const
{
	auto found = std::find_if(uniforms.begin(), uniforms.end(), [&p_name](const UniformInfo& p_element)
	{
		return p_name == p_element.name;
	});

	if (found != uniforms.end())
		return &*found;
	else
		return nullptr;
}

#pragma once

#include "GeRendering/Resources/Shader.h"

namespace GeRendering::Resources::Loaders
{
  //负责着色器的创建和销毁
	class ShaderLoader
	{
	public:
		ShaderLoader() = delete;

    //创建着色器
		static Shader* Create(const std::string& p_filePath);

		//创建着色器
		static Shader* CreateFromSource(const std::string& p_vertexShader, const std::string& p_fragmentShader);

		//重新编译一个着色器
		static void	Recompile(Shader& p_shader, const std::string& p_filePath);

    //销毁一个着色器
		static bool Destroy(Shader*& p_shader);

	private:
		static std::pair<std::string, std::string> ParseShader(const std::string& p_filePath);
		static uint32_t CreateProgram(const std::string& p_vertexShader, const std::string& p_fragmentShader);
		static uint32_t CompileShader(uint32_t p_type, const std::string& p_source);

		static std::string __FILE_TRACE;
	};
}

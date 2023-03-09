#pragma once

#include <unordered_map>

#include <GeMaths/FVector2.h>
#include <GeMaths/FVector3.h>
#include <GeMaths/FVector4.h>
#include <GeMaths/FMatrix4.h>

#include "GeRendering/Resources/UniformInfo.h"



namespace GeRendering::Resources
{
	namespace Loaders { class ShaderLoader; }

	class Shader
	{
	friend class Loaders::ShaderLoader;

	public:
		void Bind() const;
		void Unbind() const;

    //通过着色器统一向 GPU 发送一个整数
		void SetUniformInt(const std::string& p_name, int p_value);

    //通过着色器统一向 GPU 发送一个浮点数
		void SetUniformFloat(const std::string& p_name, float p_value);

    //通过着色器统一向 GPU 发送一个Vec2
		void SetUniformVec2(const std::string& p_name, const GeMaths::FVector2& p_vec2);

    //通过着色器统一向 GPU 发送一个Vec3
		void SetUniformVec3(const std::string& p_name, const GeMaths::FVector3& p_vec3);

    //通过着色器统一向 GPU 发送一个Vec4
		void SetUniformVec4(const std::string& p_name, const GeMaths::FVector4& p_vec4);

    //通过着色器统一向 GPU 发送一个Mat4
		void SetUniformMat4(const std::string& p_name, const GeMaths::FMatrix4& p_mat4);

    //返回由给定名称标识的 int 统一值
		int GetUniformInt(const std::string& p_name);

    //返回由给定名称标识的 float 统一值
		float GetUniformFloat(const std::string& p_name);

    //返回由给定名称标识的 Vec2 统一值
		GeMaths::FVector2 GetUniformVec2(const std::string& p_name);

    //返回由给定名称标识的 Vec3 统一值
		GeMaths::FVector3 GetUniformVec3(const std::string& p_name);

    //返回由给定名称标识的 Vec4 统一值
		GeMaths::FVector4 GetUniformVec4(const std::string& p_name);

    //返回由给定名称标识的 Mat4 统一值
		GeMaths::FMatrix4 GetUniformMat4(const std::string& p_name);

    //获取uniform信息
    const UniformInfo* GetUniformInfo(const std::string& p_name) const;

    //从程序中查询统一值并将它们存储在同样值向量中
		void QueryUniforms();

	private:
		Shader(const std::string p_path, uint32_t p_id);
		~Shader();

		static bool IsEngineUBOMember(const std::string& p_uniformName);
		uint32_t GetUniformLocation(const std::string& name);

	public:
		const uint32_t id;
		const std::string path;
		std::vector<UniformInfo> uniforms;

	private:
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}

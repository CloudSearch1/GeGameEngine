#pragma once

#include <any>
#include <map>

#include <GeRendering/Resources/Shader.h>

#include "GeCore/API/ISerializable.h"


namespace GeCore::Resources
{
  //材质是着色器和一些设置的组合（Material settings and shader settings）
	class Material : public API::ISerializable
	{
	public:
    //定义附加到该材质实例的着色器
		void SetShader(GeRendering::Resources::Shader* p_shader);

    //用默认统一值填充uniform
		void FillUniform();

    //绑定材质并将其统一数据发送给GPU
		void Bind(GeRendering::Resources::Texture* p_emptyTexture);

    //解绑素材
		void UnBind();

    //设置着色器统一值
		template<typename T> void Set(const std::string p_key, const T& p_value);

    //设置着色器统一值
		template<typename T> const T& Get(const std::string p_key);

    //返回附加的着色器
		GeRendering::Resources::Shader*& GetShader();

    //如果材质附加了着色器则返回真
		bool HasShader() const;

    //定义材料是否可混合
		void SetBlendable(bool p_blendable);

    //定义材质是否有背面剔除
		void SetBackfaceCulling(bool p_backfaceCulling);

    //定义材质是否有正面剔除
		void SetFrontfaceCulling(bool p_frontfaceCulling);

    //定义材料是否有深度测试
		void SetDepthTest(bool p_depthTest);

    //定义材质是否有深度书写
		void SetDepthWriting(bool p_depthWriting);

    //定义材质是否有颜色书写
		void SetColorWriting(bool p_colorWriting);

    //定义实例数
		void SetGPUInstances(int p_instances);

    //如果材料是可混合的则返回真
		bool IsBlendable() const;

    //如果材质有背面剔除则返回真
		bool HasBackfaceCulling() const;

    //如果材质有正面剔除则返回真
		bool HasFrontfaceCulling() const;

    //如果材料有深度测试则返回真
		bool HasDepthTest() const;

    //如果材质具有深度书写，则返回真
		bool HasDepthWriting() const;

    //如果材料有颜色书写则返回真
		bool HasColorWriting() const;

    //返回实例数
		int GetGPUInstances() const;

    //使用当前材质设置生成 OpenGL 状态掩码
		uint8_t GenerateStateMask() const;

    //返回材质的制服数据
		std::map<std::string, std::any>& GetUniformsData();

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		const std::string path;

	private:
		GeRendering::Resources::Shader* m_shader = nullptr;
		std::map<std::string, std::any> m_uniformsData;

		bool m_blendable		= false;
		bool m_backfaceCulling	= true;
		bool m_frontfaceCulling = false;
		bool m_depthTest		= true;
		bool m_depthWriting		= true;
		bool m_colorWriting		= true;
		int m_gpuInstances		= 1;
	};
}

#include "GeCore/Resources/Material.inl"

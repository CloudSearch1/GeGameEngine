#pragma once

#include "GeRendering/LowRenderer/Camera.h"
#include "AComponent.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //代表相机实体。 它的位置将决定它的视图矩阵
	class CCamera : public AComponent
	{
	public:
		CCamera(ECS::Actor& p_owner);

		~CCamera() = default;

    //返回组件的名称
		std::string GetName() override;

    //将相机的 fov 设置为给定值
		void SetFov(float p_value);

    //将相机的大小设置为给定值
    void SetSize(float p_value);

    //将相机的附近设置为给定值
		void SetNear(float p_value);

    //将相机的远距离设置为给定值
		void SetFar(float p_value);

    //将相机的清晰颜色设置为给定值
		void SetClearColor(const GeMaths::FVector3& p_clearColor);

    //定义相机是否应在渲染中应用平截头体几何剔除
		void SetFrustumGeometryCulling(bool p_enable);

    //定义相机是否应在渲染中应用平截头体光剔除
		void SetFrustumLightCulling(bool p_enable);

    //定义相机应采用的投影模式
    void SetProjectionMode(GeRendering::Settings::EProjectionMode p_projectionMode);

    //返回相机的 fov
		float GetFov() const;

    //返回相机的大小
    float GetSize() const;

    //返回相机附近
		float GetNear() const;

    //返回相机的远
		float GetFar() const;

    //返回相机的清除颜色
		const GeMaths::FVector3& GetClearColor() const;

    //如果启用了截头体几何剔除，则返回 true
		bool HasFrustumGeometryCulling() const;

    //如果启用了视锥光剔除，则返回 true
		bool HasFrustumLightCulling() const;

    //返回当前投影模式
    GeRendering::Settings::EProjectionMode GetProjectionMode() const;

    //返回附加到该组件的 GeRendering 相机实例
		GeRendering::LowRenderer::Camera& GetCamera();

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

	private:
		GeRendering::LowRenderer::Camera m_camera;
	};
}

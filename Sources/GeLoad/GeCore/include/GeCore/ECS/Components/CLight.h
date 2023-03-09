#pragma once

#include <GeRendering/Entities/Light.h>

#include "GeCore/ECS/Components/AComponent.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //任何灯的基类
	class CLight : public AComponent
	{
	public:
		CLight(ECS::Actor& p_owner);

    //返回光数据
		const GeRendering::Entities::Light& GetData() const;

    //返回光的颜色
		const GeMaths::FVector3& GetColor() const;

    //返回光照强度
		float GetIntensity() const;

    //定义光的新颜色
		void SetColor(const GeMaths::FVector3& p_color);

    //定义光的强度
		void SetIntensity(float p_intensity);

    //序列化组件
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //反序列化组件
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

	protected:
		GeRendering::Entities::Light m_data;
	};
}

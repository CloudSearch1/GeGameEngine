#pragma once

#include "GeCore/ECS/Components/CLight.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //没有衰减且有方向的简单光
	class CDirectionalLight : public CLight
	{
	public:
		CDirectionalLight(ECS::Actor& p_owner);

    //返回组件的名称
		std::string GetName() override;

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;
	};
}

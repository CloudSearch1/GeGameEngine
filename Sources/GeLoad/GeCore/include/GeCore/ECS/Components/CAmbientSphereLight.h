#pragma once

#include "GeCore/ECS/Components/CLight.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //表示具有球体形状的环境光
	class CAmbientSphereLight : public CLight
	{
	public:
		CAmbientSphereLight(ECS::Actor& p_owner);

    //返回组件的名称
		std::string GetName() override;

    //返回球体的半径
		float GetRadius() const;

    //定义球体的半径
		void SetRadius(float p_radius);

    //序列化组件
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //反序列化组件
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;
	};
}

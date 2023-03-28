#pragma once

#include "GeCore/ECS/Components/AComponent.h"

#include "GeCore/ECS/Components/CPhysicalObject.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //表示一个球体形状的物理对象
	class CPhysicalSphere : public CPhysicalObject
	{
	public:
		CPhysicalSphere(ECS::Actor& p_owner);

		std::string GetName() override;

    //定义球体形状的半径
		void SetRadius(float p_radius);

    //返回球体形状的半径
		float GetRadius() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;
	};
}

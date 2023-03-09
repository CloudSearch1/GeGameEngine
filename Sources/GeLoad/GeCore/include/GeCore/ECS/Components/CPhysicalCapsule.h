#pragma once

#include "GeCore/ECS/Components/AComponent.h"

#include "GeCore/ECS/Components/CPhysicalObject.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //用胶囊 hape 表示一个物理对象
	class CPhysicalCapsule : public CPhysicalObject
	{
	public:
		CPhysicalCapsule(ECS::Actor& p_owner);

		std::string GetName() override;

    //定义胶囊形状的半径
		void SetRadius(float p_radius);

    //定义胶囊形状的高度
		void SetHeight(float p_height);

    //返回胶囊形状的半径
		float GetRadius() const;

    //返回胶囊形状的高度
		float GetHeight() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;
	};
}

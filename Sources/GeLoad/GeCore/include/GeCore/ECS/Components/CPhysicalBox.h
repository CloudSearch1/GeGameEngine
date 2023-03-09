#pragma once

#include "GeCore/ECS/Components/AComponent.h"

#include "GeCore/ECS/Components/CPhysicalObject.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //用盒子形状表示一个物理对象
	class CPhysicalBox : public CPhysicalObject
	{
	public:
		CPhysicalBox(ECS::Actor& p_owner);

		std::string GetName() override;

    //定义盒子形状的大小
		void SetSize(const GeMaths::FVector3& p_size);

    //返回盒子形状的大小
		GeMaths::FVector3 GetSize() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;
	};
}

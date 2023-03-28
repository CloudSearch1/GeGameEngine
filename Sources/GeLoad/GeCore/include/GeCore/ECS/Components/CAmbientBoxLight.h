#pragma once

#include "GeCore/ECS/Components/CLight.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  // 代表一个盒子形状的环境光
	class CAmbientBoxLight : public CLight
	{
	public:
		CAmbientBoxLight(ECS::Actor& p_owner);

    // 返回组件的名称
		std::string GetName() override;

    // 返回框的大小
		GeMaths::FVector3 GetSize() const;

    // 定义盒子的大小
		void SetSize(const GeMaths::FVector3& p_size);

    // 序列化组件
    virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    // 反序列化组件
    virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    // 定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;
	};
}

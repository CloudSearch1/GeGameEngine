#pragma once

#include <GeRendering/Geometry/Vertex.h>
#include <GeRendering/Resources/Model.h>

#include "GeCore/ECS/Components/AComponent.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //ModelRenderer 必须与 MaterialRenderer 结合才能在世界中渲染模型
	class CModelRenderer : public AComponent
	{
	public:
    //定义应如何解释模型渲染器包围球
		enum class EFrustumBehaviour
		{
			DISABLED = 0,
			CULL_MODEL = 1,
			CULL_MESHES = 2,
			CULL_CUSTOM = 3
		};

		CModelRenderer(ECS::Actor& p_owner);

		std::string GetName() override;

    //定义要使用的模型
		void SetModel(GeRendering::Resources::Model* p_model);

    //返回当前模型
		GeRendering::Resources::Model* GetModel() const;

    //设置边界模式
		void SetFrustumBehaviour(EFrustumBehaviour p_boundingMode);

    //返回当前的边界模式
		EFrustumBehaviour GetFrustumBehaviour() const;

    //返回自定义包围球
		const GeRendering::Geometry::BoundingSphere& GetCustomBoundingSphere() const;

    //设置自定义包围球
		void SetCustomBoundingSphere(const GeRendering::Geometry::BoundingSphere& p_boundingSphere);

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

	private:
		GeRendering::Resources::Model* m_model = nullptr;
		GeUtils::Eventing::Event<> m_modelChangedEvent;
		GeRendering::Geometry::BoundingSphere m_customBoundingSphere = { {}, 1.0f };
		EFrustumBehaviour m_frustumBehaviour = EFrustumBehaviour::CULL_MODEL;
	};
}

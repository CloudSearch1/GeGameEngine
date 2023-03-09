
#include "GeCore/ECS/Components/CLight.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //局域化、有衰减且有方向的光
	class CSpotLight : public CLight
	{
	public:
		CSpotLight(ECS::Actor& p_owner);

		std::string GetName() override;

    //返回光常量
		float GetConstant() const;

    //返回光线线性
		float GetLinear() const;

    //返回光的二次方
		float GetQuadratic() const;

    //返回光截止
		float GetCutoff() const;

    //返回 light outercutoff
		float GetOuterCutoff() const;

    //定义光照常数
		void SetConstant(float p_constant);

    //定义光线线性
		void SetLinear(float p_linear);

    //定义光的二次方
		void SetQuadratic(float p_quadratic);

    //定义光截止
		void SetCutoff(float p_cutoff);

    //定义光outercutoff
		void SetOuterCutoff(float p_outerCutoff);

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;
	};
}

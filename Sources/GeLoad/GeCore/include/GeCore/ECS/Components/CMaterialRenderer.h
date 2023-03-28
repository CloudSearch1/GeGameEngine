#pragma once

#include <array>

#include <GeUI/Widgets/Layout/Columns.h>

#include <GeRendering/Resources/Mesh.h>

#include "GeCore/Resources/Material.h"
#include "GeCore/ECS/Components/AComponent.h"

#define MAX_MATERIAL_COUNT 255

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //处理材料列表的组件，模型渲染所必需的
	class CMaterialRenderer : public AComponent
	{
	public:
		using MaterialList = std::array<GeCore::Resources::Material*, MAX_MATERIAL_COUNT>;
		using MaterialField = std::array<std::array<GeUI::Widgets::AWidget*, 3>, MAX_MATERIAL_COUNT>;

    CMaterialRenderer(ECS::Actor& p_owner);

    //返回组件的名称
		std::string GetName() override;

    //用给定的材质填充材质渲染器
		void FillWithMaterial(GeCore::Resources::Material& p_material);

    //定义用于给定索引的材料
		void SetMaterialAtIndex(uint8_t p_index, GeCore::Resources::Material& p_material);

    //返回在索引处使用的材料
		GeCore::Resources::Material* GetMaterialAtIndex(uint8_t p_index);

    //移除索引处的材料
		void RemoveMaterialAtIndex(uint8_t p_index);

    //按实例移除材质
		void RemoveMaterialByInstance(GeCore::Resources::Material& p_instance);

    //删除所有材料
		void RemoveAllMaterials();

    //通过获取模型信息更新材质列表
		void UpdateMaterialList();

    //定义用户矩阵的一个元素
		void SetUserMatrixElement(uint32_t p_row, uint32_t p_column, float p_value);

    //返回用户矩阵的一个元素
		float GetUserMatrixElement(uint32_t p_row, uint32_t p_column) const;

    //返回用户矩阵
		const GeMaths::FMatrix4& GetUserMatrix() const;

    //返回材料
		const MaterialList& GetMaterials() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

	private:
		MaterialList m_materials;
		MaterialField m_materialFields;
		std::array<std::string, MAX_MATERIAL_COUNT> m_materialNames;
		GeMaths::FMatrix4 m_userMatrix;
	};
}

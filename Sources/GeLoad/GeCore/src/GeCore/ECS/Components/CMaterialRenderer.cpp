#include <GeUI/Widgets/InputFields/InputInt.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Buttons/Button.h>
#include <GeUI/Widgets/Buttons/ButtonSmall.h>
#include <GeUI/Widgets/Texts/TextColored.h>
#include <GeUI/Plugins/DDTarget.h>

#include <GeUtils/Utils/PathParser.h>

#include "GeCore/ECS/Actor.h"
#include "GeCore/ECS/Components/CMaterialRenderer.h"
#include "GeCore/ECS/Components/CModelRenderer.h"
#include "GeCore/ResourceManagement/MaterialManager.h"
#include "GeCore/Global/ServiceLocator.h"

GeCore::ECS::Components::CMaterialRenderer::CMaterialRenderer(ECS::Actor & p_owner) : AComponent(p_owner)
{
	m_materials.fill(nullptr);

	for (uint8_t i = 0; i < MAX_MATERIAL_COUNT; ++i)
		m_materialFields[i].fill(nullptr);

	UpdateMaterialList();
}

std::string GeCore::ECS::Components::CMaterialRenderer::GetName()
{
	return "Material Renderer";
}

void GeCore::ECS::Components::CMaterialRenderer::FillWithMaterial(GeCore::Resources::Material & p_material)
{
	for (uint8_t i = 0; i < m_materials.size(); ++i)
		m_materials[i] = &p_material;
}

void GeCore::ECS::Components::CMaterialRenderer::SetMaterialAtIndex(uint8_t p_index, GeCore::Resources::Material& p_material)
{
	m_materials[p_index] = &p_material;
}

GeCore::Resources::Material* GeCore::ECS::Components::CMaterialRenderer::GetMaterialAtIndex(uint8_t p_index)
{
	return m_materials.at(p_index);
}

void GeCore::ECS::Components::CMaterialRenderer::RemoveMaterialAtIndex(uint8_t p_index)
{
	if (p_index < m_materials.size())
	{
		m_materials[p_index] = nullptr;;
	}
}

void GeCore::ECS::Components::CMaterialRenderer::RemoveMaterialByInstance(GeCore::Resources::Material& p_instance)
{
	for (uint8_t i = 0; i < m_materials.size(); ++i)
		if (m_materials[i] == &p_instance)
			m_materials[i] = nullptr;
}

void GeCore::ECS::Components::CMaterialRenderer::RemoveAllMaterials()
{
	for (uint8_t i = 0; i < m_materials.size(); ++i)
		m_materials[i] = nullptr;
}

const GeMaths::FMatrix4 & GeCore::ECS::Components::CMaterialRenderer::GetUserMatrix() const
{
	return m_userMatrix;
}

const GeCore::ECS::Components::CMaterialRenderer::MaterialList& GeCore::ECS::Components::CMaterialRenderer::GetMaterials() const
{
	return m_materials;
}

void GeCore::ECS::Components::CMaterialRenderer::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	tinyxml2::XMLNode* materialsNode = p_doc.NewElement("materials");
	p_node->InsertEndChild(materialsNode);

	auto modelRenderer = owner.GetComponent<CModelRenderer>();
	uint8_t elementsToSerialize = modelRenderer->GetModel() ? (uint8_t)std::min(modelRenderer->GetModel()->GetMaterialNames().size(), (size_t)MAX_MATERIAL_COUNT) : 0;

	for (uint8_t i = 0; i < elementsToSerialize; ++i)
	{
		GeCore::Helpers::Serializer::SerializeMaterial(p_doc, materialsNode, "material", m_materials[i]);
	}
}

void GeCore::ECS::Components::CMaterialRenderer::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	tinyxml2::XMLNode* materialsRoot = p_node->FirstChildElement("materials");
	if (materialsRoot)
	{
		tinyxml2::XMLElement* currentMaterial = materialsRoot->FirstChildElement("material");

		uint8_t materialIndex = 0;

		while (currentMaterial)
		{
			if (auto material = Global::ServiceLocator::Get<ResourceManagement::MaterialManager>()[currentMaterial->GetText()])
				m_materials[materialIndex] = material;

			currentMaterial = currentMaterial->NextSiblingElement("material");
			++materialIndex;
		}
	}

	UpdateMaterialList();
}

std::array<GeUI::Widgets::AWidget*, 3> CustomMaterialDrawer(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeCore::Resources::Material*& p_data)
{
	using namespace GeCore::Helpers;

	std::array<GeUI::Widgets::AWidget*, 3> widgets;

	widgets[0] = &p_root.CreateWidget<GeUI::Widgets::Texts::TextColored>(p_name, GUIDrawer::TitleColor);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto & rightSide = p_root.CreateWidget<GeUI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<GeUI::Widgets::Texts::Text>(displayedText);

	widgets[1] = &widget;

	widget.AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data](auto p_receivedData)
	{
		if (GeUtils::Utils::PathParser::GetFileType(p_receivedData.first) == GeUtils::Utils::PathParser::EFileType::MATERIAL)
		{
			if (auto resource = OVSERVICE(GeCore::ResourceManagement::MaterialManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
			}
		}
	};

	widget.lineBreak = false;

	auto & resetButton = rightSide.CreateWidget<GeUI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = GUIDrawer::ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data]
	{
		p_data = nullptr;
		widget.content = "Empty";
	};

	widgets[2] = &resetButton;

	return widgets;
}

void GeCore::ECS::Components::CMaterialRenderer::OnInspector(GeUI::Internal::WidgetContainer & p_root)
{
	using namespace GeCore::Helpers;

	for (uint8_t i = 0; i < m_materials.size(); ++i)
		m_materialFields[i] = CustomMaterialDrawer(p_root, "Material", m_materials[i]);

	UpdateMaterialList();
}

void GeCore::ECS::Components::CMaterialRenderer::UpdateMaterialList()
{
	if (auto modelRenderer = owner.GetComponent<CModelRenderer>(); modelRenderer && modelRenderer->GetModel())
	{
		uint8_t materialIndex = 0;

		for (const std::string& materialName : modelRenderer->GetModel()->GetMaterialNames())
		{
			m_materialNames[materialIndex++] = materialName;
		}

		for (uint8_t i = materialIndex; i < MAX_MATERIAL_COUNT; ++i)
			m_materialNames[i] = "";
	}

	for (uint8_t i = 0; i < m_materialFields.size(); ++i)
	{
		if (m_materialFields[i][0])
		{
			bool enabled = !m_materialNames[i].empty();
			m_materialFields[i][0]->enabled = enabled;
			m_materialFields[i][1]->enabled = enabled;
			m_materialFields[i][2]->enabled = enabled;
			reinterpret_cast<GeUI::Widgets::Texts::Text*>(m_materialFields[i][0])->content = m_materialNames[i];
		}
	}
}

void GeCore::ECS::Components::CMaterialRenderer::SetUserMatrixElement(uint32_t p_row, uint32_t p_column, float p_value)
{
	if (p_row < 4 && p_column < 4)
		m_userMatrix.data[4 * p_row + p_column] = p_value;
}

float GeCore::ECS::Components::CMaterialRenderer::GetUserMatrixElement(uint32_t p_row, uint32_t p_column) const
{
	if (p_row < 4 && p_column < 4)
		return m_userMatrix.data[4 * p_row + p_column];
	else
		return 0.0f;
}

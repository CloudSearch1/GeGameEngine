/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Layout/Columns.h>
#include <GeRendering/Resources/Shader.h>

namespace GeCore::Resources { class Material; }

namespace GeEditor::Panels
{
	class MaterialEditor : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		MaterialEditor
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Refresh the material editor
		*/
		void Refresh();

		/**
		* Defines the target material of the material editor
		* @param p_newTarget
		*/
		void SetTarget(GeCore::Resources::Material& p_newTarget);

		/**
		* Returns the target of the material editor
		*/
		GeCore::Resources::Material* GetTarget() const;

		/**
		* Remove the target of the material editor (Clear the material editor)
		*/
		void RemoveTarget();

		/**
		* Launch the preview of the currently targeted material
		*/
		void Preview();

		/**
		* Reset material
		*/
		void Reset();
		
	private:
		void OnMaterialDropped();
		void OnShaderDropped();

		void CreateHeaderButtons();
		void CreateMaterialSelector();
		void CreateShaderSelector();
		void CreateMaterialSettings();
		void CreateShaderSettings();

		void GenerateShaderSettingsContent();
		void GenerateMaterialSettingsContent();

	private:
		GeCore::Resources::Material* m_target		= nullptr;
		GeRendering::Resources::Shader* m_shader	= nullptr;

		GeUI::Widgets::Texts::Text* m_targetMaterialText	= nullptr;
		GeUI::Widgets::Texts::Text* m_shaderText			= nullptr;

		GeUtils::Eventing::Event<> m_materialDroppedEvent;
		GeUtils::Eventing::Event<> m_shaderDroppedEvent;

		GeUI::Widgets::Layout::Group* m_settings			= nullptr;
		GeUI::Widgets::Layout::Group* m_materialSettings	= nullptr;
		GeUI::Widgets::Layout::Group* m_shaderSettings		= nullptr;

		GeUI::Widgets::Layout::Columns<2>* m_shaderSettingsColumns = nullptr;
		GeUI::Widgets::Layout::Columns<2>* m_materialSettingsColumns = nullptr;
	};
}
/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <variant>

#include <GeUtils/Filesystem/IniFile.h>
#include <GeUtils/Eventing/Event.h>

#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Layout/Columns.h>

#include <GeRendering/Resources/Model.h>
#include <GeRendering/Resources/Texture.h>

namespace GeEditor::Panels
{
	class AssetProperties : public GeUI::Panels::PanelWindow
	{
	public:
		using EditableAssets = std::variant<GeRendering::Resources::Model*, GeRendering::Resources::Texture*>;

		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		AssetProperties
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Defines the target of the asset settings editor
		* @param p_path
		*/
		void SetTarget(const std::string& p_path);

        /**
        * Refresh the panel to show the current target settings
        */
        void Refresh();

		/**
		* Launch the preview of the target asset
		*/
		void Preview();

	private:
		void CreateHeaderButtons();
        void CreateAssetSelector();
		void CreateSettings();
		void CreateInfo();
		void CreateModelSettings();
		void CreateTextureSettings();
		void Apply();

	private:
		std::string m_resource;

        GeUtils::Eventing::Event<> m_targetChanged;
        GeUI::Widgets::Layout::Group* m_settings = nullptr;
        GeUI::Widgets::Layout::Group* m_info = nullptr;
        GeUI::Widgets::Buttons::Button* m_applyButton = nullptr;
        GeUI::Widgets::Buttons::Button* m_revertButton = nullptr;
        GeUI::Widgets::Buttons::Button* m_previewButton = nullptr;
        GeUI::Widgets::Buttons::Button* m_resetButton = nullptr;
        GeUI::Widgets::AWidget* m_headerSeparator = nullptr;
        GeUI::Widgets::AWidget* m_headerLineBreak = nullptr;
		GeUI::Widgets::Layout::Columns<2>* m_settingsColumns = nullptr;
		GeUI::Widgets::Layout::Columns<2>* m_infoColumns = nullptr;
        GeUI::Widgets::Texts::Text* m_assetSelector = nullptr;
		std::unique_ptr<GeUtils::Filesystem::IniFile> m_metadata;
	};
}
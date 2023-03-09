/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <filesystem>
#include <unordered_map>
#include <queue>

#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Layout/TreeNode.h>
#include <GeRendering/Resources/Loaders/TextureLoader.h>

namespace GeEditor::Panels
{
	/**
	* A panel that handle asset management
	*/
	class AssetBrowser : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @parma p_opened
		* @param p_windowSettings
		* @param p_engineAssetFolder
		* @param p_projectAssetFolder
		* @param p_projectScriptFolder
		*/
		AssetBrowser
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings,
			const std::string& p_engineAssetFolder = "",
			const std::string& p_projectAssetFolder = "",
			const std::string& p_projectScriptFolder = ""
		);

		/**
		* Fill the asset browser panels with widgets corresponding to elements in the asset folder
		*/
		void Fill();

		/**
		* Clear the asset browser widgets
		*/
		void Clear();

		/**
		* Refresh the asset browser widgets (Clear + Fill)
		*/
		void Refresh();

	private:
		void ParseFolder(GeUI::Widgets::Layout::TreeNode& p_root, const std::filesystem::directory_entry& p_directory, bool p_isEngineItem, bool p_scriptFolder = false);
		void ConsiderItem(GeUI::Widgets::Layout::TreeNode* p_root, const std::filesystem::directory_entry& p_entry, bool p_isEngineItem, bool p_autoOpen = false, bool p_scriptFolder = false);

	public:
		static const std::string __FILENAMES_CHARS;

	private:
		std::string m_engineAssetFolder;
		std::string m_projectAssetFolder;
		std::string m_projectScriptFolder;
		GeUI::Widgets::Layout::Group* m_assetList;
		std::unordered_map<GeUI::Widgets::Layout::TreeNode*, std::string> m_pathUpdate;
	};
}
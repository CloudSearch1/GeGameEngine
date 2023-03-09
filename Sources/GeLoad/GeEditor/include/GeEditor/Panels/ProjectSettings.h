/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Panels/PanelWindow.h>

#include <GeUtils/Filesystem/IniFile.h>

namespace GeEditor::Panels
{
	class ProjectSettings : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		ProjectSettings
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Generate a gatherer that will get the value associated to the given key
		* @param p_keyName
		*/
		template <typename T>
		std::function<T()> GenerateGatherer(const std::string& p_keyName)
		{
			return std::bind(&GeUtils::Filesystem::IniFile::Get<T>, &m_projectFile, p_keyName);
		}

		/**
		* Generate a provider that will set the value associated to the given key
		* @param p_keyName
		*/
		template <typename T>
		std::function<void(T)> GenerateProvider(const std::string& p_keyName)
		{
			return std::bind(&GeUtils::Filesystem::IniFile::Set<T>, &m_projectFile, p_keyName, std::placeholders::_1);
		}

	private:
		GeUtils::Filesystem::IniFile& m_projectFile;
	};
}
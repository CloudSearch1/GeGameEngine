/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "GeUI/Plugins/IPlugin.h"
#include "GeUI/Internal/WidgetContainer.h"
#include "GeUI/Widgets/Menu/MenuList.h"
#include "GeUI/Widgets/Menu/MenuItem.h"

namespace GeUI::Plugins
{
	/**
	* A simple plugin that will show a contextual menu on right click
	* You can add widgets to a contextual menu
	*/
	class ContextualMenu : public IPlugin, public Internal::WidgetContainer
	{
	public:
		/**
		* Execute the plugin
		*/
		void Execute();

		/**
		* Force close the contextual menu
		*/
		void Close();
	};
}

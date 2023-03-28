/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeUtils/Eventing/Event.h>

#include "GeUI/Widgets/Texts/Text.h"

namespace GeUI::Widgets::Texts
{
	/**
	* Simple widget to display a selectable text on a panel
	*/
	class TextSelectable : public Text
	{
	public:
		/**
		* Constructor
		* @param p_content
		* @param p_selected
		* @param p_disabled
		*/
		TextSelectable(const std::string& p_content = "", bool p_selected = false, bool p_disabled = false);

	protected:
		virtual void _Draw_Impl() override;

	public:
		bool selected;
		bool disabled;

		GeUtils::Eventing::Event<bool> ClickedEvent;
		GeUtils::Eventing::Event<> SelectedEvent;
		GeUtils::Eventing::Event<> UnselectedEvent;
	};
}
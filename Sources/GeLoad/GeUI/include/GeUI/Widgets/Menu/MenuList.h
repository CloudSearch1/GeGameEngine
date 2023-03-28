/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <vector>

#include <GeUtils/Eventing/Event.h>

#include "GeUI/Widgets/Layout/Group.h"

namespace GeUI::Widgets::Menu
{
	/**
	* Widget that behave like a group with a menu display
	*/
	class MenuList : public Layout::Group
	{
	public:
		/**
		* Constructor
		* @param p_name
		* @param p_locked
		*/
		MenuList(const std::string& p_name, bool p_locked = false);

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;
		bool locked;
		GeUtils::Eventing::Event<> ClickedEvent;

	private:
		bool m_opened;
	};
}
/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <vector>

#include <GeUtils/Eventing/Event.h>

#include "GeUI/Widgets/Layout/Group.h"

namespace GeUI::Widgets::Layout
{
	/**
	* Widget that can contains other widgets and is collapsable
	*/
	class GroupCollapsable : public Group
	{
	public:
		/**
		* Constructor
		* @param p_name
		*/
		GroupCollapsable(const std::string& p_name = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;
		bool closable = false;
		bool opened = true;
		GeUtils::Eventing::Event<> CloseEvent;
		GeUtils::Eventing::Event<> OpenEvent;
	};
}
/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include <GeUtils/Eventing/Event.h>

#include "GeUI/Widgets/AWidget.h"

namespace GeUI::Widgets::Buttons
{
	/**
	* Base class for any button widget
	*/
	class AButton : public AWidget
	{
	protected:
		void _Draw_Impl() override = 0;

	public:
		GeUtils::Eventing::Event<> ClickedEvent;
	};
}
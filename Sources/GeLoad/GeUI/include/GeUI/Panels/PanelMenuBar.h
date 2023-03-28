/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include <GeUtils/Eventing/Event.h>

#include "GeUI/Panels/APanel.h"
#include "GeUI/Widgets/Menu/MenuList.h"

namespace GeUI::Panels
{
	/**
	* A simple panel that will be displayed on the top side of the canvas
	*/
	class PanelMenuBar : public APanel
	{
	protected:
		void _Draw_Impl() override;
	};
}
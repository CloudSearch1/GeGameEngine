/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <vector>

#include "GeUI/Internal/WidgetContainer.h"

namespace GeUI::Widgets::Layout
{
	/**
	* Widget that can contains other widgets
	*/
	class Group : public AWidget, public Internal::WidgetContainer
	{
	protected:
		virtual void _Draw_Impl() override;
	};
}
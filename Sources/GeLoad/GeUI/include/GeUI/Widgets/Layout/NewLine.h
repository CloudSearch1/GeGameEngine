/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "GeUI/Widgets/AWidget.h"

namespace GeUI::Widgets::Layout
{
	/**
	* Widget that adds an empty line to the panel
	*/
	class NewLine : public AWidget
	{
	protected:
		void _Draw_Impl() override;
	};
}
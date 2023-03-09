/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeUtils/Eventing/Event.h>

#include "GeUI/Widgets/DataWidget.h"
#include "GeUI/Types/Color.h"

namespace GeUI::Widgets::Selection
{
	/**
	* Widget that can open a color picker on click
	*/
	class ColorEdit : public DataWidget<Types::Color>
	{
	public:
		/**
		* Constructor
		* @param p_enableAlpha
		* @param p_defaultColor
		*/
		ColorEdit(bool p_enableAlpha = false, const Types::Color& p_defaultColor = {});

	protected:
		void _Draw_Impl() override;

	public:
		bool enableAlpha;
		Types::Color color;
		GeUtils::Eventing::Event<Types::Color&> ColorChangedEvent;
	};
}
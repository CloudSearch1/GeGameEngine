/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include "GeUI/Widgets/Buttons/AButton.h"
#include "GeUI/Types/Color.h"

namespace GeUI::Widgets::Buttons
{
	/**
	* Small button widget
	*/
	class ButtonSmall : public AButton
	{
	public:
		/**
		* Constructor
		* @param p_label
		*/
		ButtonSmall(const std::string& p_label = "");

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;

		Types::Color idleBackgroundColor;
		Types::Color hoveredBackgroundColor;
		Types::Color clickedBackgroundColor;

		Types::Color textColor;
	};
}
/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include <GeMaths/FVector2.h>

#include "GeUI/Widgets/Buttons/AButton.h"
#include "GeUI/Types/Color.h"

namespace GeUI::Widgets::Buttons
{
	/**
	* Simple button widget
	*/
	class Button : public AButton
	{
	public:
		/**
		* Constructor
		* @param p_label
		* @param p_size
		* @param p_disabled
		*/
		Button(const std::string& p_label = "", const GeMaths::FVector2& p_size = GeMaths::FVector2(0.f, 0.f), bool p_disabled = false);

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;
		GeMaths::FVector2 size;
		bool disabled = false;

		Types::Color idleBackgroundColor;
		Types::Color hoveredBackgroundColor;
		Types::Color clickedBackgroundColor;

		Types::Color textColor;
	};
}
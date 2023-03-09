/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include <GeMaths/FVector2.h>

#include "GeUI/Types/Color.h"
#include "GeUI/Widgets/Buttons/AButton.h"

namespace GeUI::Widgets::Buttons
{
	/**
	* Button widget of a single color (Color palette element)
	*/
	class ButtonColored : public AButton
	{
	public:
		/**
		* Constructor
		* @param p_label
		* @param p_color
		* @param p_size
		* @param p_enableAlpha
		*/
		ButtonColored(const std::string& p_label = "", const Types::Color& p_color = {}, const GeMaths::FVector2& p_size =GeMaths::FVector2(0.f, 0.f), bool p_enableAlpha = true);

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;
		Types::Color color;
		GeMaths::FVector2 size;
		bool enableAlpha;
	};
}
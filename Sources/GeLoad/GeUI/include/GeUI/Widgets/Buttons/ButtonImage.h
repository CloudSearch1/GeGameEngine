/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeMaths/FVector2.h>

#include "GeUI/Internal/TextureID.h"
#include "GeUI/Types/Color.h"
#include "GeUI/Widgets/Buttons/AButton.h"

namespace GeUI::Widgets::Buttons
{
	/**
	* Button widget with an image
	*/
	class ButtonImage : public AButton
	{
	public:
		/**
		* Constructor
		* @param p_textureID
		* @param p_size
		*/
		ButtonImage(uint32_t p_textureID, const GeMaths::FVector2& p_size);

	protected:
		void _Draw_Impl() override;

	public:
		bool disabled = false;

		GeUI::Types::Color background = { 0, 0, 0, 0 };
		GeUI::Types::Color tint = { 1, 1, 1, 1 };

		Internal::TextureID textureID;
		GeMaths::FVector2 size;
	};
}
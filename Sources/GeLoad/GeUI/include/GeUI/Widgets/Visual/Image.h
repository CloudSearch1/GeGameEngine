/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeMaths/FVector2.h>

#include "GeUI/Internal/TextureID.h"
#include "GeUI/Widgets/AWidget.h"

namespace GeUI::Widgets::Visual
{
	/**
	* Simple widget that display an image
	*/
	class Image : public AWidget
	{
	public:
		/**
		* Constructor
		* @param p_textureID
		* @parma p_size
		*/
		Image(uint32_t p_textureID, const GeMaths::FVector2& p_size);

	protected:
		void _Draw_Impl() override;

	public:
		Internal::TextureID textureID;
		GeMaths::FVector2 size;
	};
}
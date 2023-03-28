/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeMaths/FVector2.h>

#include "GeUI/Widgets/AWidget.h"

namespace GeUI::Widgets::Layout
{
	/**
	* Dummy widget that takes the given size as space in the panel
	*/
	class Dummy : public AWidget
	{
	public:
		/**
		* Constructor
		* @param p_size
		*/
		Dummy(const GeMaths::FVector2& p_size = { 0.0f, 0.0f });

	protected:
		void _Draw_Impl() override;

	public:
		GeMaths::FVector2 size;
	};
}
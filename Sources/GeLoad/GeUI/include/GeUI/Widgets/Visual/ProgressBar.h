/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeMaths/FVector2.h>

#include "GeUI/Widgets/AWidget.h"

namespace GeUI::Widgets::Visual
{
	/**
	* Simple widget that display a progress bar
	*/
	class ProgressBar : public AWidget
	{
	public:
		/**
		* Constructor
		* @param p_fraction
		* @param p_size
		* @param p_overlay
		*/
		ProgressBar(float p_fraction = 0.0f, const GeMaths::FVector2& p_size = { 0.0f, 0.0f }, const std::string& p_overlay = "");

	protected:
		void _Draw_Impl() override;

	public:
		float fraction;
		GeMaths::FVector2 size;
		std::string overlay;
	};
}
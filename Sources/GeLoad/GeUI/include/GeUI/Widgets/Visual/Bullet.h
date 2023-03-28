/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "GeUI/Widgets/AWidget.h"

namespace GeUI::Widgets::Visual
{
	/**
	* Simple widget that display a bullet point
	*/
	class Bullet : public AWidget
	{
	protected:
		virtual void _Draw_Impl() override;
	};
}
/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "GeUI/Panels/APanelTransformable.h"

namespace GeUI::Panels
{
	/**
	* A simple panel that is transformable and without decorations (No background)
	*/
	class PanelUndecorated : public APanelTransformable
	{
	public:
		void _Draw_Impl() override;

	private:
		int CollectFlags();
	};
}
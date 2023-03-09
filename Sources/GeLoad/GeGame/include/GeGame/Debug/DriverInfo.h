#pragma once

#ifdef _DEBUG

#include <GeRendering/Core/Renderer.h>
#include <GeWindow/Window.h>

#include <GeUI/Panels/PanelUndecorated.h>
#include <GeUI/Widgets/Texts/TextColored.h>

namespace GeGame::Debug
{
	class DriverInfo : public GeUI::Panels::PanelUndecorated
	{
	public:
		DriverInfo(GeRendering::Core::Renderer& p_renderer, GeWindow::Window& p_window);
	};
}

#endif

#pragma once

#include <GeRendering/Core/Renderer.h>
#include <GeWindow/Context/Device.h>
#include <GeWindow/Window.h>
#include <GeRendering/Context/Driver.h>
#include <GeUI/Core/UIManager.h>
#include <GeUI/Panels/PanelWindow.h>

namespace GeEditor::Core
{
	class ProjectHub
	{
	public:
		ProjectHub();

		std::tuple<bool, std::string, std::string> Run();

		void SetupContext();

		void RegisterProject(const std::string& p_path);

	private:
		std::unique_ptr<GeWindow::Context::Device> m_device;
		std::unique_ptr<GeWindow::Window> m_window;
		std::unique_ptr<GeRendering::Context::Driver> m_driver;
		std::unique_ptr<GeRendering::Core::Renderer> m_renderer;
		std::unique_ptr<GeUI::Core::UIManager> m_uiManager;

		GeUI::Modules::Canvas m_canvas;
		std::unique_ptr<GeUI::Panels::PanelWindow> m_mainPanel;

		std::string m_projectPath = "";
		std::string m_projectName = "";
		bool m_readyToGo = false;
	};
}

/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#define _CRT_SECURE_NO_WARNINGS

#include <filesystem>
#include <fstream>

#include "GeEditor/Core/ProjectHub.h"

#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Widgets/Visual/Separator.h>
#include <GeUI/Widgets/Layout/Columns.h>
#include <GeUI/Widgets/Layout/Spacing.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Buttons/Button.h>
#include <GeUI/Widgets/InputFields/InputText.h>

#include <GeUtils/Utils/PathParser.h>

#include <GeWindow/Dialogs/SaveFileDialog.h>
#include <GeWindow/Dialogs/OpenFileDialog.h>
#include <GeWindow/Dialogs/MessageBox.h>

#define PROJECTS_FILE std::string(std::string(getenv("APPDATA")) + "\\OverloadTech\\GeEditor\\projects.ini")

class ProjectHubPanel : public GeUI::Panels::PanelWindow
{
public:
	ProjectHubPanel(bool& p_readyToGo, std::string& p_path, std::string& p_projectName) :
		PanelWindow("Overload - Project Hub", true),
		m_readyToGo(p_readyToGo),
		m_path(p_path),
		m_projectName(p_projectName)
	{
		resizable = false;
		movable = false;
		titleBar = false;

		std::filesystem::create_directories(std::string(getenv("APPDATA")) + "\\OverloadTech\\GeEditor\\");

		SetSize({ 1000, 580 });
		SetPosition({ 0.f, 0.f });

		auto& openProjectButton = CreateWidget<GeUI::Widgets::Buttons::Button>("Open Project");
		auto& newProjectButton = CreateWidget<GeUI::Widgets::Buttons::Button>("New Project");
		auto& pathField = CreateWidget<GeUI::Widgets::InputFields::InputText>("");
		m_goButton = &CreateWidget<GeUI::Widgets::Buttons::Button>("GO");

		pathField.ContentChangedEvent += [this, &pathField](std::string p_content)
		{
			pathField.content = GeUtils::Utils::PathParser::MakeWindowsStyle(p_content);

			if (pathField.content != "" && pathField.content.back() != '\\')
				pathField.content += '\\';

			UpdateGoButton(pathField.content);
		};

		UpdateGoButton("");

		openProjectButton.idleBackgroundColor = { 0.7f, 0.5f, 0.f };
		newProjectButton.idleBackgroundColor = { 0.f, 0.5f, 0.0f };

		openProjectButton.ClickedEvent += [this]
		{
			GeWindow::Dialogs::OpenFileDialog dialog("Open project");
			dialog.AddFileType("Overload Project", "*.ovproject");
			dialog.Show();

			std::string ovProjectPath = dialog.GetSelectedFilePath();
			std::string rootFolderPath = GeUtils::Utils::PathParser::GetContainingFolder(ovProjectPath);

			if (dialog.HasSucceeded())
			{
				RegisterProject(rootFolderPath);
				OpenProject(rootFolderPath);
			}
		};

		newProjectButton.ClickedEvent += [this, &pathField]
		{
			GeWindow::Dialogs::SaveFileDialog dialog("New project location");
			dialog.DefineExtension("Overload Project", "..");
			dialog.Show();
			if (dialog.HasSucceeded())
			{
				std::string result = dialog.GetSelectedFilePath();
				pathField.content = std::string(result.data(), result.data() + result.size() - std::string("..").size()); // remove auto extension
				pathField.content += "\\";
				UpdateGoButton(pathField.content);
			}
		};

		m_goButton->ClickedEvent += [this, &pathField]
		{
			CreateProject(pathField.content);
			RegisterProject(pathField.content);
			OpenProject(pathField.content);
		};

		openProjectButton.lineBreak = false;
		newProjectButton.lineBreak = false;
		pathField.lineBreak = false;

		for (uint8_t i = 0; i < 4; ++i)
			CreateWidget<GeUI::Widgets::Layout::Spacing>();

		CreateWidget<GeUI::Widgets::Visual::Separator>();

		for (uint8_t i = 0; i < 4; ++i)
			CreateWidget<GeUI::Widgets::Layout::Spacing>();

		auto& columns = CreateWidget<GeUI::Widgets::Layout::Columns<2>>();

		columns.widths = { 750, 500 };

		std::string line;
		std::ifstream myfile(PROJECTS_FILE);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				if (std::filesystem::exists(line)) // TODO: Delete line from the file
				{
					auto& text = columns.CreateWidget<GeUI::Widgets::Texts::Text>(line);
					auto& actions = columns.CreateWidget<GeUI::Widgets::Layout::Group>();
					auto& openButton = actions.CreateWidget<GeUI::Widgets::Buttons::Button>("Open");
					auto& deleteButton = actions.CreateWidget<GeUI::Widgets::Buttons::Button>("Delete");

					openButton.idleBackgroundColor = { 0.7f, 0.5f, 0.f };
					deleteButton.idleBackgroundColor = { 0.5f, 0.f, 0.f };

					openButton.ClickedEvent += [this, line]
					{
						OpenProject(line);
					};

					std::string toErase = line;
					deleteButton.ClickedEvent += [this, &text, &actions, toErase]
					{
						text.Destroy();
						actions.Destroy();

						std::string line;
						std::ifstream fin(PROJECTS_FILE);
						std::ofstream temp("temp");

						while (getline(fin, line))
							if (line != toErase)
								temp << line << std::endl;

						temp.close();
						fin.close();

						std::filesystem::remove(PROJECTS_FILE);
						std::filesystem::rename("temp", PROJECTS_FILE);
					};

					openButton.lineBreak = false;
					deleteButton.lineBreak;
				}
			}
			myfile.close();
		}
	}

	void UpdateGoButton(const std::string& p_path)
	{
		bool validPath = p_path != "";
		m_goButton->idleBackgroundColor = validPath ? GeUI::Types::Color{ 0.f, 0.5f, 0.0f } : GeUI::Types::Color{ 0.1f, 0.1f, 0.1f };
		m_goButton->disabled = !validPath;
	}

	void CreateProject(const std::string& p_path)
	{
		if (!std::filesystem::exists(p_path))
		{
			std::filesystem::create_directory(p_path);
			std::filesystem::create_directory(p_path + "Assets\\");
			std::filesystem::create_directory(p_path + "Scripts\\");
			std::ofstream projectFile(p_path + '\\' + GeUtils::Utils::PathParser::GetElementName(std::string(p_path.data(), p_path.data() + p_path.size() - 1)) + ".ovproject");
		}
	}

	void RegisterProject(const std::string& p_path)
	{
		bool pathAlreadyRegistered = false;

		{
			std::string line;
			std::ifstream myfile(PROJECTS_FILE);
			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					if (line == p_path)
					{
						pathAlreadyRegistered = true;
						break;
					}
				}
				myfile.close();
			}
		}

		if (!pathAlreadyRegistered)
		{
			std::ofstream projectsFile(PROJECTS_FILE, std::ios::app);
			projectsFile << p_path << std::endl;
		}
	}
	
	void OpenProject(const std::string& p_path)
	{
		m_readyToGo = std::filesystem::exists(p_path);
		if (!m_readyToGo)
		{
			using namespace GeWindow::Dialogs;
			MessageBox errorMessage("Project not found", "The selected project does not exists", MessageBox::EMessageType::ERROR, MessageBox::EButtonLayout::OK);
		}
		else
		{
			m_path = p_path;
			m_projectName = GeUtils::Utils::PathParser::GetElementName(m_path);
			Close();
		}
	}

	void Draw() override
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 50.f, 50.f });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);

		GeUI::Panels::PanelWindow::Draw();

		ImGui::PopStyleVar(2);
	}

private:
	bool& m_readyToGo;
	std::string& m_path;
	std::string& m_projectName;
	GeUI::Widgets::Buttons::Button* m_goButton = nullptr;
};

GeEditor::Core::ProjectHub::ProjectHub()
{
	SetupContext();
	m_mainPanel = std::make_unique<ProjectHubPanel>(m_readyToGo, m_projectPath, m_projectName);

	m_uiManager->SetCanvas(m_canvas);
	m_canvas.AddPanel(*m_mainPanel);
}

std::tuple<bool, std::string, std::string> GeEditor::Core::ProjectHub::Run()
{
	m_renderer->SetClearColor(0.f, 0.f, 0.f, 1.f);

	while (!m_window->ShouldClose())
	{
		m_renderer->Clear();
		m_device->PollEvents();
		m_uiManager->Render();
		m_window->SwapBuffers();

		if (!m_mainPanel->IsOpened())
			m_window->SetShouldClose(true);
	}

	return { m_readyToGo, m_projectPath, m_projectName };
}

void GeEditor::Core::ProjectHub::SetupContext()
{
	/* Settings */
	GeWindow::Settings::DeviceSettings deviceSettings;
	GeWindow::Settings::WindowSettings windowSettings;
	windowSettings.title = "Overload - Project Hub";
	windowSettings.width = 1000;
	windowSettings.height = 580;
	windowSettings.maximized = false;
	windowSettings.resizable = false;
	windowSettings.decorated = true;

	/* Window creation */
	m_device = std::make_unique<GeWindow::Context::Device>(deviceSettings);
	m_window = std::make_unique<GeWindow::Window>(*m_device, windowSettings);
	m_window->MakeCurrentContext();

	auto[monWidth, monHeight] = m_device->GetMonitorSize();
	auto[winWidth, winHeight] = m_window->GetSize();
	m_window->SetPosition(monWidth / 2 - winWidth / 2, monHeight / 2 - winHeight / 2);

	/* Graphics context creation */
	m_driver = std::make_unique<GeRendering::Context::Driver>(GeRendering::Settings::DriverSettings{ false });
	m_renderer = std::make_unique<GeRendering::Core::Renderer>(*m_driver);
	m_renderer->SetCapability(GeRendering::Settings::ERenderingCapability::MULTISAMPLE, true);

	m_uiManager = std::make_unique<GeUI::Core::UIManager>(m_window->GetGlfwWindow(), GeUI::Styling::EStyle::ALTERNATIVE_DARK);
	m_uiManager->LoadFont("Ruda_Big", "Data\\Editor\\Fonts\\Ruda-Bold.ttf", 18);
	m_uiManager->UseFont("Ruda_Big");
	m_uiManager->EnableEditorLayoutSave(false);
	m_uiManager->EnableDocking(false);
}

void GeEditor::Core::ProjectHub::RegisterProject(const std::string& p_path)
{
	static_cast<ProjectHubPanel*>(m_mainPanel.get())->RegisterProject(p_path);
}

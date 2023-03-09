#include <filesystem>

#include <GeUtils/Utils/String.h>

#include <GeRendering/Utils/Defines.h>

#include "GeEditor/Core/ProjectHub.h"
#include "GeEditor/Core/Application.h"

#undef APIENTRY
#include "Windows.h"

FORCE_DEDICATED_GPU

void UpdateWorkingDirectory(const std::string& p_executablePath)
{
	if (!IsDebuggerPresent())
	{
		std::filesystem::current_path(GeUtils::Utils::PathParser::GetContainingFolder(p_executablePath));
	}
}

int main(int argc, char** argv);
static void TryRun(const std::string& projectPath, const std::string& projectName);

#ifndef _DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	main(__argc, __argv);
}
#endif

int main(int argc, char** argv)
{
	UpdateWorkingDirectory(argv[0]);

	bool ready = false;
	std::string projectPath;
	std::string projectName;

	{
		GeEditor::Core::ProjectHub hub;

		if (argc < 2)
		{
			std::tie(ready, projectPath, projectName) = hub.Run();
		}
		else
		{
			std::string projectFile = argv[1];

			if (GeUtils::Utils::PathParser::GetExtension(projectFile) == "ovproject")
			{
				ready = true;
				projectPath = GeUtils::Utils::PathParser::GetContainingFolder(projectFile);
				projectName = GeUtils::Utils::PathParser::GetElementName(projectFile);
				GeUtils::Utils::String::Replace(projectName, ".ovproject", "");
			}

			hub.RegisterProject(projectPath);
		}
	}

	if (ready)
		TryRun(projectPath, projectName);

	return EXIT_SUCCESS;
}

static void TryRun(const std::string& projectPath, const std::string& projectName)
{
	auto errorEvent =
		[](GeWindow::Context::EDeviceError, std::string errMsg)
		{
			errMsg = "Overload requires OpenGL 4.3 or newer.\r\n" + errMsg;
			MessageBox(0, errMsg.c_str(), "Overload", MB_OK | MB_ICONSTOP);
		};

	std::unique_ptr<GeEditor::Core::Application> app;

	try
	{
		auto listenerId = GeWindow::Context::Device::ErrorEvent += errorEvent;
		app = std::make_unique<GeEditor::Core::Application>(projectPath, projectName);
		GeWindow::Context::Device::ErrorEvent -= listenerId;
	}
	catch (...) {}

	if (app)
		app->Run();
}

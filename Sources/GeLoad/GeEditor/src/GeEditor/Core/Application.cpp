#include <GeUtils/Time/Clock.h>

#include "GeEditor/Core/Application.h"

GeEditor::Core::Application::Application(const std::string& p_projectPath, const std::string& p_projectName) :
	m_context(p_projectPath, p_projectName),
	m_editor(m_context)
{
}

GeEditor::Core::Application::~Application()
{
}

void GeEditor::Core::Application::Run()
{
	GeUtils::Time::Clock clock;

	while (IsRunning())
	{
		m_editor.PreUpdate();
		m_editor.Update(clock.GetDeltaTime());
		m_editor.PostUpdate();

		clock.Update();
	}
}

bool GeEditor::Core::Application::IsRunning() const
{
	return !m_context.window->ShouldClose();
}

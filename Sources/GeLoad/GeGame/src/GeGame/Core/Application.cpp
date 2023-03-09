#include <GeUtils/Time/Clock.h>

#include "GeGame/Core/Application.h"

GeGame::Core::Application::Application() :
	m_game(m_context)
{

}

GeGame::Core::Application::~Application()
{
}

void GeGame::Core::Application::Run()
{
	GeUtils::Time::Clock clock;

	while (IsRunning())
	{
		m_game.PreUpdate();
		m_game.Update(clock.GetDeltaTime());
		m_game.PostUpdate();

		clock.Update();
	}
}

bool GeGame::Core::Application::IsRunning() const
{
	return !m_context.window->ShouldClose();
}

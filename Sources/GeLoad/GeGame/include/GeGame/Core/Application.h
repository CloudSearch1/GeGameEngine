#pragma once

#include "GeGame/Core/Context.h"
#include "GeGame/Core/Game.h"

namespace GeGame::Core
{
	class Application
	{
	public:
		Application();

		~Application();

		void Run();

		bool IsRunning() const;

	private:
		Context m_context;
		Game m_game;
	};
}

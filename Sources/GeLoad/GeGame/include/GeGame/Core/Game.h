#pragma once

#include <GeUI/Modules/Canvas.h>
#include <GeCore/ECS/Components/CCamera.h>

#include "GeGame/Core/Context.h"
#include "GeGame/Core/GameRenderer.h"

#include "GeGame/Utils/FPSCounter.h"

#ifdef _DEBUG
#include "GeGame/Debug/DriverInfo.h"
#include "GeGame/Debug/GameProfiler.h"
#include "GeGame/Debug/FrameInfo.h"
#endif

namespace GeGame::Core
{
	class Game
	{
	public:
		Game(Context& p_context);

		~Game();

		void PreUpdate();

		void Update(float p_deltaTime);

		void PostUpdate();

	private:
		float m_elapsed = 0.0f;

		GeGame::Core::Context& m_context;
		GeUI::Modules::Canvas m_canvas;

		GeGame::Core::GameRenderer m_gameRenderer;

		GeGame::Utils::FPSCounter	m_fpsCounter;

		#ifdef _DEBUG
		GeGame::Debug::DriverInfo	m_driverInfo;
		GeGame::Debug::GameProfiler m_gameProfiler;
		GeGame::Debug::FrameInfo	m_frameInfo;
		#endif

		#ifdef _DEBUG
		bool m_showDebugInformation = true;
		#else
		bool m_showDebugInformation = false;
		#endif
	};
}

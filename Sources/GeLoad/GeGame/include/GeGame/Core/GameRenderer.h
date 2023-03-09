#pragma once

#include <GeCore/ECS/Actor.h>
#include <GeCore/SceneSystem/SceneManager.h>
#include <GeCore/ECS/Components/CCamera.h>

#include "GeGame/Core/Context.h"

namespace GeGame::Core
{
	class GameRenderer
	{
	public:
		GameRenderer(Context& p_context);

		void RenderScene();

		void UpdateEngineUBO(GeCore::ECS::Components::CCamera& p_mainCamera);

		void UpdateLights(GeCore::SceneSystem::Scene& p_scene);

		void UpdateLightsInFrustum(GeCore::SceneSystem::Scene& p_scene, const GeRendering::Data::Frustum& p_frustum);

	private:
		Context& m_context;
		GeCore::Resources::Material m_emptyMaterial;
	};
}

/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "GeEditor/Panels/AViewControllable.h"
#include "GeEditor/Core/GizmoBehaviour.h"

namespace GeEditor::Panels
{
	class SceneView : public GeEditor::Panels::AViewControllable
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		SceneView
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Update the scene view
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Custom implementation of the render method
		*/
		virtual void _Render_Impl() override;

		/**
		* Render the actual scene
		* @param p_defaultRenderState
		*/
		void RenderScene(uint8_t p_defaultRenderState);

		/**
		* Render the scene for actor picking (Using unlit colors)
		*/
		void RenderSceneForActorPicking();

		/**
		* Render the scene for actor picking and handle the logic behind it
		*/
		void HandleActorPicking();

	private:
		GeCore::SceneSystem::SceneManager& m_sceneManager;
		GeRendering::Buffers::Framebuffer m_actorPickingFramebuffer;
		GeEditor::Core::GizmoBehaviour m_gizmoOperations;
		GeEditor::Core::EGizmoOperation m_currentOperation = GeEditor::Core::EGizmoOperation::TRANSLATE;

		std::optional<std::reference_wrapper<GeCore::ECS::Actor>> m_highlightedActor;
		std::optional<GeEditor::Core::GizmoBehaviour::EDirection> m_highlightedGizmoDirection;
	};
}
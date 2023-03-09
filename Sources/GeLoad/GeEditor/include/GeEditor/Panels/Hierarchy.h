/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeRendering/Resources/Loaders/TextureLoader.h>
#include <GeRendering/LowRenderer/Camera.h>

#include <GeCore/SceneSystem/SceneManager.h>

#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Layout/TreeNode.h>

namespace GeEditor::Panels
{
	class Hierarchy : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		Hierarchy
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);
		
		/**
		* Clear hierarchy nodes
		*/
		void Clear();

		/**
		* Unselect every widgets
		*/
		void UnselectActorsWidgets();

		/**
		* Select the widget corresponding to the given actor
		* @param p_actor
		*/
		void SelectActorByInstance(GeCore::ECS::Actor& p_actor);

		/**
		* Select the widget
		* @param p_actor
		*/
		void SelectActorByWidget(GeUI::Widgets::Layout::TreeNode& p_widget);

		/**
		* Attach the given actor linked widget to its parent widget
		* @param p_actor
		*/
		void AttachActorToParent(GeCore::ECS::Actor& p_actor);

		/**
		* Detach the given actor linked widget from its parent widget
		* @param p_actor
		*/
		void DetachFromParent(GeCore::ECS::Actor& p_actor);

		/**
		* Delete the widget referencing the given actor
		* @param p_actor
		*/
		void DeleteActorByInstance(GeCore::ECS::Actor& p_actor);

		/**
		* Add a widget referencing the given actor
		* @param p_actor
		*/
		void AddActorByInstance(GeCore::ECS::Actor& p_actor);

	public:
		GeUtils::Eventing::Event<GeCore::ECS::Actor&> ActorSelectedEvent;
		GeUtils::Eventing::Event<GeCore::ECS::Actor&> ActorUnselectedEvent;

	private:
		GeUI::Widgets::Layout::TreeNode* m_sceneRoot;

		std::unordered_map<GeCore::ECS::Actor*, GeUI::Widgets::Layout::TreeNode*> m_widgetActorLink;
	};
}
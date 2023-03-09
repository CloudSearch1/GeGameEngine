/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeRendering/Resources/Loaders/TextureLoader.h>

#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Layout/GroupCollapsable.h>
#include <GeUI/Widgets/InputFields/InputText.h>
#include <GeUI/Widgets/Visual/Separator.h>
#include <GeUI/Widgets/Selection/CheckBox.h>
#include <GeUI/Widgets/Buttons/Button.h>
#include <GeUI/Widgets/Selection/ComboBox.h>

#include "GeEditor/Panels/Hierarchy.h"
#include "GeEditor/Panels/AssetBrowser.h"

namespace GeEditor::Panels
{
	class Inspector : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		Inspector
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Destructor
		*/
		~Inspector();

		/**
		* Focus the given actor
		* @param p_target
		*/
		void FocusActor(GeCore::ECS::Actor& p_target);

		/**
		* Unfocus the currently targeted actor
		*/
		void UnFocus();

		/**
		* Unfocus the currently targeted actor without removing listeners attached to this actor
		*/
		void SoftUnFocus();

		/**
		* Returns the currently selected actor
		*/
		GeCore::ECS::Actor* GetTargetActor() const;

		/**
		* Create the actor inspector for the given actor
		*/
		void CreateActorInspector(GeCore::ECS::Actor& p_target);

		/**
		* Draw the given component in inspector
		*/
		void DrawComponent(GeCore::ECS::Components::AComponent& p_component);

		/**
		* Draw the given behaviour in inspector
		*/
		void DrawBehaviour(GeCore::ECS::Components::Behaviour& p_behaviour);

		/**
		* Refresh the inspector
		*/
		void Refresh();

	private:
		GeCore::ECS::Actor* m_targetActor = nullptr;
		GeUI::Widgets::Layout::Group* m_actorInfo;
		GeUI::Widgets::Layout::Group* m_inspectorHeader;
		GeUI::Widgets::Selection::ComboBox* m_componentSelectorWidget;
        GeUI::Widgets::InputFields::InputText* m_scriptSelectorWidget;

		uint64_t m_componentAddedListener	= 0;
		uint64_t m_componentRemovedListener = 0;
		uint64_t m_behaviourAddedListener	= 0;
		uint64_t m_behaviourRemovedListener = 0;
		uint64_t m_destroyedListener		= 0;
	};
}
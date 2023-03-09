/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <map>

#include "GeEditor/Panels/Inspector.h"

#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Widgets/Buttons/Button.h>
#include <GeUI/Widgets/Drags/DragMultipleFloats.h>
#include <GeUI/Widgets/Drags/DragFloat.h>
#include <GeUI/Widgets/Layout/Spacing.h>
#include <GeUI/Widgets/Layout/Columns.h>
#include <GeUI/Widgets/Visual/Image.h>
#include <GeUI/Widgets/InputFields/InputFloat.h>
#include <GeUI/Widgets/Selection/ColorEdit.h>
#include <GeUI/Plugins/DDTarget.h>

#include <GeCore/Global/ServiceLocator.h>
#include <GeCore/ResourceManagement/ModelManager.h>
#include <GeCore/ResourceManagement/TextureManager.h>
#include <GeCore/ResourceManagement/ShaderManager.h>

#include <GeCore/ECS/Components/CTransform.h>
#include <GeCore/ECS/Components/CModelRenderer.h>
#include <GeCore/ECS/Components/CCamera.h>
#include <GeCore/ECS/Components/CPhysicalBox.h>
#include <GeCore/ECS/Components/CPhysicalSphere.h>
#include <GeCore/ECS/Components/CPhysicalCapsule.h>
#include <GeCore/ECS/Components/CPointLight.h>
#include <GeCore/ECS/Components/CDirectionalLight.h>
#include <GeCore/ECS/Components/CSpotLight.h>
#include <GeCore/ECS/Components/CAmbientBoxLight.h>
#include <GeCore/ECS/Components/CMaterialRenderer.h>
#include <GeCore/ECS/Components/CAudioSource.h>
#include <GeCore/ECS/Components/CAudioListener.h>

#include <GeWindow/Dialogs/MessageBox.h>

#include "GeEditor/Core/EditorActions.h"

using namespace GeCore::ECS::Components;
using namespace GeUI::Widgets;

GeEditor::Panels::Inspector::Inspector
(
	const std::string& p_title,
	bool p_opened,
	const GeUI::Settings::PanelWindowSettings & p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings)
{
	m_inspectorHeader = &CreateWidget<GeUI::Widgets::Layout::Group>();
	m_inspectorHeader->enabled = false;
	m_actorInfo = &CreateWidget<GeUI::Widgets::Layout::Group>();

	auto& headerColumns = m_inspectorHeader->CreateWidget<GeUI::Widgets::Layout::Columns<2>>();

	/* Name field */
	auto nameGatherer = [this] { return m_targetActor ? m_targetActor->GetName() : "%undef%"; };
	auto nameProvider = [this](const std::string& p_newName) { if (m_targetActor) m_targetActor->SetName(p_newName); };
	GeCore::Helpers::GUIDrawer::DrawString(headerColumns, "Name", nameGatherer, nameProvider);

	/* Tag field */
	auto tagGatherer = [this] { return m_targetActor ? m_targetActor->GetTag() : "%undef%"; };
	auto tagProvider = [this](const std::string & p_newName) { if (m_targetActor) m_targetActor->SetTag(p_newName); };
	GeCore::Helpers::GUIDrawer::DrawString(headerColumns, "Tag", tagGatherer, tagProvider);

	/* Active field */
	auto activeGatherer = [this] { return m_targetActor ? m_targetActor->IsSelfActive() : false; };
	auto activeProvider = [this](bool p_active) { if (m_targetActor) m_targetActor->SetActive(p_active); };
	GeCore::Helpers::GUIDrawer::DrawBoolean(headerColumns, "Active", activeGatherer, activeProvider);

	/* Component select + button */
	{
		auto& componentSelectorWidget = m_inspectorHeader->CreateWidget<GeUI::Widgets::Selection::ComboBox>(0);
		componentSelectorWidget.lineBreak = false;
		componentSelectorWidget.choices.emplace(0, "Model Renderer");
		componentSelectorWidget.choices.emplace(1, "Camera");
		componentSelectorWidget.choices.emplace(2, "Physical Box");
		componentSelectorWidget.choices.emplace(3, "Physical Sphere");
		componentSelectorWidget.choices.emplace(4, "Physical Capsule");
		componentSelectorWidget.choices.emplace(5, "Point Light");
		componentSelectorWidget.choices.emplace(6, "Directional Light");
		componentSelectorWidget.choices.emplace(7, "Spot Light");
		componentSelectorWidget.choices.emplace(8, "Ambient Box Light");
		componentSelectorWidget.choices.emplace(9, "Ambient Sphere Light");
		componentSelectorWidget.choices.emplace(10, "Material Renderer");
		componentSelectorWidget.choices.emplace(11, "Audio Source");
		componentSelectorWidget.choices.emplace(12, "Audio Listener");

		auto& addComponentButton = m_inspectorHeader->CreateWidget<GeUI::Widgets::Buttons::Button>("Add Component", GeMaths::FVector2{ 100.f, 0 });
		addComponentButton.idleBackgroundColor = GeUI::Types::Color{ 0.7f, 0.5f, 0.f };
		addComponentButton.textColor = GeUI::Types::Color::White;
		addComponentButton.ClickedEvent += [&componentSelectorWidget, this]
		{
			switch (componentSelectorWidget.currentChoice)
			{
			case 0: GetTargetActor()->AddComponent<CModelRenderer>(); GetTargetActor()->AddComponent<CMaterialRenderer>(); break;
			case 1: GetTargetActor()->AddComponent<CCamera>();				break;
			case 2: GetTargetActor()->AddComponent<CPhysicalBox>();			break;
			case 3: GetTargetActor()->AddComponent<CPhysicalSphere>();		break;
			case 4: GetTargetActor()->AddComponent<CPhysicalCapsule>();		break;
			case 5: GetTargetActor()->AddComponent<CPointLight>();			break;
			case 6: GetTargetActor()->AddComponent<CDirectionalLight>();	break;
			case 7: GetTargetActor()->AddComponent<CSpotLight>();			break;
			case 8: GetTargetActor()->AddComponent<CAmbientBoxLight>();		break;
			case 9: GetTargetActor()->AddComponent<CAmbientSphereLight>();	break;
			case 10: GetTargetActor()->AddComponent<CMaterialRenderer>();	break;
			case 11: GetTargetActor()->AddComponent<CAudioSource>();		break;
			case 12: GetTargetActor()->AddComponent<CAudioListener>();		break;
			}

			componentSelectorWidget.ValueChangedEvent.Invoke(componentSelectorWidget.currentChoice);
		};

		componentSelectorWidget.ValueChangedEvent += [this, &addComponentButton](int p_value)
		{
			auto defineButtonsStates = [&addComponentButton](bool p_componentExists)
			{
				addComponentButton.disabled = p_componentExists;
				addComponentButton.idleBackgroundColor = !p_componentExists ? GeUI::Types::Color{ 0.7f, 0.5f, 0.f } : GeUI::Types::Color{ 0.1f, 0.1f, 0.1f };
			};

			switch (p_value)
			{
			case 0: defineButtonsStates(GetTargetActor()->GetComponent<CModelRenderer>());		return;
			case 1: defineButtonsStates(GetTargetActor()->GetComponent<CCamera>());				return;
			case 2: defineButtonsStates(GetTargetActor()->GetComponent<CPhysicalObject>());		return;
			case 3: defineButtonsStates(GetTargetActor()->GetComponent<CPhysicalObject>());		return;
			case 4: defineButtonsStates(GetTargetActor()->GetComponent<CPhysicalObject>());		return;
			case 5: defineButtonsStates(GetTargetActor()->GetComponent<CPointLight>());			return;
			case 6: defineButtonsStates(GetTargetActor()->GetComponent<CDirectionalLight>());	return;
			case 7: defineButtonsStates(GetTargetActor()->GetComponent<CSpotLight>());			return;
			case 8: defineButtonsStates(GetTargetActor()->GetComponent<CAmbientBoxLight>());	return;
			case 9: defineButtonsStates(GetTargetActor()->GetComponent<CAmbientSphereLight>());	return;
			case 10: defineButtonsStates(GetTargetActor()->GetComponent<CMaterialRenderer>());	return;
			case 11: defineButtonsStates(GetTargetActor()->GetComponent<CAudioSource>());		return;
			case 12: defineButtonsStates(GetTargetActor()->GetComponent<CAudioListener>());		return;
			}
		};

		m_componentSelectorWidget = &componentSelectorWidget;
	}

	/* Script selector + button */
	{
		m_scriptSelectorWidget = &m_inspectorHeader->CreateWidget<GeUI::Widgets::InputFields::InputText>("");
        m_scriptSelectorWidget->lineBreak = false;
		auto& ddTarget = m_scriptSelectorWidget->AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, Layout::Group*>>>("File");
		
		auto& addScriptButton = m_inspectorHeader->CreateWidget<GeUI::Widgets::Buttons::Button>("Add Script", GeMaths::FVector2{ 100.f, 0 });
		addScriptButton.idleBackgroundColor = GeUI::Types::Color{ 0.7f, 0.5f, 0.f };
		addScriptButton.textColor = GeUI::Types::Color::White;

        // Add script button state updater
        const auto updateAddScriptButton = [&addScriptButton, this](const std::string& p_script)
        {
            const std::string realScriptPath = EDITOR_CONTEXT(projectScriptsPath) + p_script + ".lua";

            const auto targetActor = GetTargetActor();
            const bool isScriptValid = std::filesystem::exists(realScriptPath) && targetActor && !targetActor->GetBehaviour(p_script);

            addScriptButton.disabled = !isScriptValid;
            addScriptButton.idleBackgroundColor = isScriptValid ? GeUI::Types::Color{ 0.7f, 0.5f, 0.f } : GeUI::Types::Color{ 0.1f, 0.1f, 0.1f };
        };

        m_scriptSelectorWidget->ContentChangedEvent += updateAddScriptButton;

		addScriptButton.ClickedEvent += [updateAddScriptButton, this]
		{
            const std::string realScriptPath = EDITOR_CONTEXT(projectScriptsPath) + m_scriptSelectorWidget->content + ".lua";

            // Ensure that the script is a valid one
            if (std::filesystem::exists(realScriptPath))
            {
                GetTargetActor()->AddBehaviour(m_scriptSelectorWidget->content);
                updateAddScriptButton(m_scriptSelectorWidget->content);
            }
		};

        ddTarget.DataReceivedEvent += [updateAddScriptButton, this](std::pair<std::string, Layout::Group*> p_data)
        {
            m_scriptSelectorWidget->content = EDITOR_EXEC(GetScriptPath(p_data.first));
            updateAddScriptButton(m_scriptSelectorWidget->content);
        };
	}

	m_inspectorHeader->CreateWidget<GeUI::Widgets::Visual::Separator>();

	m_destroyedListener = GeCore::ECS::Actor::DestroyedEvent += [this](GeCore::ECS::Actor& p_destroyed)
	{ 
		if (&p_destroyed == m_targetActor)
			UnFocus();
	};
}

GeEditor::Panels::Inspector::~Inspector()
{
	GeCore::ECS::Actor::DestroyedEvent -= m_destroyedListener;

	UnFocus();
}

void GeEditor::Panels::Inspector::FocusActor(GeCore::ECS::Actor& p_target)
{
	if (m_targetActor)
		UnFocus();

	m_actorInfo->RemoveAllWidgets();

	m_targetActor = &p_target;

	m_componentAddedListener = m_targetActor->ComponentAddedEvent += [this] (auto& useless) { EDITOR_EXEC(DelayAction([this] { Refresh(); })); };
	m_behaviourAddedListener =		m_targetActor->BehaviourAddedEvent += [this](auto& useless) { EDITOR_EXEC(DelayAction([this] { Refresh(); })); };
	m_componentRemovedListener =	m_targetActor->ComponentRemovedEvent += [this](auto& useless) { EDITOR_EXEC(DelayAction([this] { Refresh(); })); };
	m_behaviourRemovedListener =	m_targetActor->BehaviourRemovedEvent += [this](auto& useless) { EDITOR_EXEC(DelayAction([this] { Refresh(); })); };

	m_inspectorHeader->enabled = true;

	CreateActorInspector(p_target);

    // Force component and script selectors to trigger their ChangedEvent to update button states
	m_componentSelectorWidget->ValueChangedEvent.Invoke(m_componentSelectorWidget->currentChoice);
    m_scriptSelectorWidget->ContentChangedEvent.Invoke(m_scriptSelectorWidget->content);

	EDITOR_EVENT(ActorSelectedEvent).Invoke(*m_targetActor);
}

void GeEditor::Panels::Inspector::UnFocus()
{
	if (m_targetActor)
	{
		m_targetActor->ComponentAddedEvent		-= m_componentAddedListener;
		m_targetActor->ComponentRemovedEvent	-= m_componentRemovedListener;
		m_targetActor->BehaviourAddedEvent		-= m_behaviourAddedListener;
		m_targetActor->BehaviourRemovedEvent	-= m_behaviourRemovedListener;
	}

	SoftUnFocus();
}

void GeEditor::Panels::Inspector::SoftUnFocus()
{
    if (m_targetActor)
    {
        EDITOR_EVENT(ActorUnselectedEvent).Invoke(*m_targetActor);
        m_inspectorHeader->enabled = false;
        m_targetActor = nullptr;
        m_actorInfo->RemoveAllWidgets();
    }
}

GeCore::ECS::Actor * GeEditor::Panels::Inspector::GetTargetActor() const
{
	return m_targetActor;
}

void GeEditor::Panels::Inspector::CreateActorInspector(GeCore::ECS::Actor& p_target)
{
	std::map<std::string, GeCore::ECS::Components::AComponent*> components;

	for (auto component : p_target.GetComponents())
		if (component->GetName() != "Transform")
			components[component->GetName()] = component.get();

	auto transform = p_target.GetComponent<GeCore::ECS::Components::CTransform>();
	if (transform)
		DrawComponent(*transform);

	for (auto& [name, instance] : components)
		DrawComponent(*instance);

	auto& behaviours = p_target.GetBehaviours();

	for (auto&[name, behaviour] : behaviours)
		DrawBehaviour(behaviour);
}

void GeEditor::Panels::Inspector::DrawComponent(GeCore::ECS::Components::AComponent& p_component)
{
	if (auto inspectorItem = dynamic_cast<GeCore::API::IInspectorItem*>(&p_component); inspectorItem)
	{
		auto& header = m_actorInfo->CreateWidget<GeUI::Widgets::Layout::GroupCollapsable>(p_component.GetName());
		header.closable = !dynamic_cast<GeCore::ECS::Components::CTransform*>(&p_component);
		header.CloseEvent += [this, &header, &p_component]
		{ 
			if (p_component.owner.RemoveComponent(p_component))
				m_componentSelectorWidget->ValueChangedEvent.Invoke(m_componentSelectorWidget->currentChoice);
		};
		auto& columns = header.CreateWidget<GeUI::Widgets::Layout::Columns<2>>();
		columns.widths[0] = 200;
		inspectorItem->OnInspector(columns);
	}
}

void GeEditor::Panels::Inspector::DrawBehaviour(GeCore::ECS::Components::Behaviour & p_behaviour)
{
	if (auto inspectorItem = dynamic_cast<GeCore::API::IInspectorItem*>(&p_behaviour); inspectorItem)
	{
		auto& header = m_actorInfo->CreateWidget<GeUI::Widgets::Layout::GroupCollapsable>(p_behaviour.name);
		header.closable = true;
		header.CloseEvent += [this, &header, &p_behaviour]
		{
			p_behaviour.owner.RemoveBehaviour(p_behaviour);
		};

		auto& columns = header.CreateWidget<GeUI::Widgets::Layout::Columns<2>>();
		columns.widths[0] = 200;
		inspectorItem->OnInspector(columns);
	}
}

void GeEditor::Panels::Inspector::Refresh()
{
	if (m_targetActor)
	{
		m_actorInfo->RemoveAllWidgets();
		CreateActorInspector(*m_targetActor);
	}
}

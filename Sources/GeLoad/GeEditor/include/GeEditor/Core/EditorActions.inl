#pragma once

#include "GeEditor/Core/EditorActions.h"

namespace GeEditor::Core
{
	template<typename T>
	inline GeCore::ECS::Actor & EditorActions::CreateMonoComponentActor(bool p_focusOnCreation, GeCore::ECS::Actor* p_parent)
	{
		auto& instance = CreateEmptyActor(false, p_parent);

		T& component = instance.AddComponent<T>();

        instance.SetName(component.GetName());

		if (p_focusOnCreation)
			SelectActor(instance);

		return instance;
	}
}

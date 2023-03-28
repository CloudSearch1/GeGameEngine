#include "GeCore/ECS/Components/AComponent.h"
#include "GeCore/ECS/Actor.h"

GeCore::ECS::Components::AComponent::AComponent(ECS::Actor& p_owner) : owner(p_owner)
{
}

GeCore::ECS::Components::AComponent::~AComponent()
{
	if (owner.IsActive())
	{
		OnDisable();
		OnDestroy();
	}
}

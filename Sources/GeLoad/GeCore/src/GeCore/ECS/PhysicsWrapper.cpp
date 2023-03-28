#include "GeCore/ECS/PhysicsWrapper.h"

#include "GeCore/Global/ServiceLocator.h"

#include <GePhysics/Core/PhysicsEngine.h>

std::optional<GeCore::ECS::PhysicsWrapper::RaycastHit> GeCore::ECS::PhysicsWrapper::Raycast(GeMaths::FVector3 p_origin, GeMaths::FVector3 p_direction, float p_distance)
{
	if (auto result = OVSERVICE(GePhysics::Core::PhysicsEngine).Raycast(p_origin, p_direction, p_distance))
	{
		RaycastHit finalResult;

		finalResult.FirstResultObject = std::addressof(result.value().FirstResultObject->GetUserData<std::reference_wrapper<Components::CPhysicalObject>>().get());
		for (auto object : result.value().ResultObjects)
			finalResult.ResultObjects.push_back(std::addressof(object->GetUserData<std::reference_wrapper<Components::CPhysicalObject>>().get()));

		return finalResult;
	}
	else
		return {};
}

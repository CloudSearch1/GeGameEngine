#pragma once

#include <optional>
#include <vector>

#include <GePhysics/Entities/RaycastHit.h>

#include <GeMaths/FVector3.h>

#include "GeCore/ECS/Components/CPhysicalObject.h"

namespace GeCore::ECS
{
  //包含 ECS 风格的 GePhysics 包装器的简单类
	class PhysicsWrapper
	{
	public:
    //用物理组件包装物理 RaycastHit 的简单数据结构
		struct RaycastHit
		{
			Components::CPhysicalObject* FirstResultObject = nullptr;
			std::vector<Components::CPhysicalObject*> ResultObjects;
		};

    //对场景中的所有物理对象投射光线并返回有关被击中的信息
		static std::optional<RaycastHit> Raycast(GeMaths::FVector3 p_origin, GeMaths::FVector3 p_direction, float p_distance);
	};
}

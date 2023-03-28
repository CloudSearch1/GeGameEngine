#pragma once

#include <bullet/btBulletCollisionCommon.h>

#include <vector>


#include "GePhysics/Entities/PhysicalObject.h"

namespace GePhysics::Entities
{
  //保存光线投射命中信息的数据结构
	struct RaycastHit
	{
		Entities::PhysicalObject* FirstResultObject = nullptr;
		std::vector<Entities::PhysicalObject*> ResultObjects;
	};
}

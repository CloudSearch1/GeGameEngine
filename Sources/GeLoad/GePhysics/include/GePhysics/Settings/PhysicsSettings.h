#pragma once

#include <GeMaths/FVector3.h>

namespace GePhysics::Settings
{
  //提供给 PhysicsEngine 构造函数以设置其设置的数据结构
	struct PhysicsSettings
	{
		GeMaths::FVector3 gravity = { 0.0f, -9.81f, 0.f };
	};
}

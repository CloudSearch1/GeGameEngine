#pragma once

#include <bullet/btBulletCollisionCommon.h>

namespace GePhysics::Settings
{
  //有用的重新创建一个身体使用其以前的设置
	struct BodySettings
	{
		btVector3 linearVelocity	= { 0.f, 0.f, 0.f };
		btVector3 angularVelocity	= { 0.f, 0.f, 0.f };
		btVector3 linearFactor		= { 1, 1, 1 };
		btVector3 angularFactor		= { 1, 1, 1 };
		float restitution			    = 0.f;
		float friction				    = 0.5f;
		bool isTrigger				    = false;
		bool isKinematic			    = false;
	};
}

#pragma once

#include <GeMaths/FVector3.h>

namespace GeRendering::Geometry
{
  //定义边界球体
	struct BoundingSphere
	{
		GeMaths::FVector3 position;
		float radius;
	};
}

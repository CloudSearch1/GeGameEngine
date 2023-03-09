#pragma once

#include <array>

#include <GeMaths/FMatrix4.h>
#include <GeMaths/FTransform.h>


#include "GeRendering/Geometry/BoundingSphere.h"

namespace GeRendering::Data
{
  //3D视锥体数学表示
	class Frustum
	{
	public:

    //更新视锥体值
		void CalculateFrustum(const GeMaths::FMatrix4& p_viewProjection);

    //返回点是否在视锥体上面
		bool PointInFrustum(float p_x, float p_y, float p_z) const;

    //返回球是否在视锥体上面
		bool SphereInFrustum(float p_x, float p_y, float p_z, float p_radius) const;

    //返回立方体是否在视锥体内
		bool CubeInFrustum(float p_x, float p_y, float p_z, float p_size) const;

    //如果给定的边界球体在截锥体中，则返回 true
		bool BoundingSphereInFrustum(const GeRendering::Geometry::BoundingSphere& p_boundingSphere, const GeMaths::FTransform& p_transform) const;

    //返回近平面
		std::array<float, 4> GetNearPlane() const;

    //返回远平面
		std::array<float, 4> GetFarPlane() const;

	private:
		float m_frustum[6][4];
	};
}

#pragma once

#include "GePhysics/Entities/PhysicalObject.h"

namespace GePhysics::Entities
{
  //具有球体形状的 PhysicalObject
	class PhysicalSphere : public PhysicalObject
	{
	public:
		
    //PhysicalSphere 构造函数（内部转换管理）
		PhysicalSphere(float p_radius = 1.f);

    //PhysicalSphere 构造函数（外部转换管理）
		PhysicalSphere(GeMaths::FTransform& p_transform, float p_radius = 1.f);

    //为球体定义一个新的半径
		void SetRadius(float p_radius);

    //返回球体的实际半径
		float GetRadius() const;

	private:
		void CreateCollisionShape(float p_radius);
		void RecreateCollisionShape(float p_radius);
		virtual void SetLocalScaling(const GeMaths::FVector3& p_scaling) override;

	private:
		float m_radius;
	};
}

#pragma once

#include "GePhysics/Entities/PhysicalObject.h"

namespace GePhysics::Entities
{
  //具有胶囊形状的 PhysicalObject
	class PhysicalCapsule : public PhysicalObject
	{
	public:
    //PhysicalCapsule 构造函数（内部转换管理）
		PhysicalCapsule(float p_radius = 1.f, float p_height = 1.f);

    //PhysicalCapsule 构造函数（外部转换管理）
		PhysicalCapsule(GeMaths::FTransform& p_transform, float p_radius = 1.f, float p_height = 1.f);
    
    //为胶囊定义一个新的半径
		void SetRadius(float p_radius);
    
    //为胶囊定义一个新的高度
		void SetHeight(float p_height);

    //返回胶囊的实际半径
		float GetRadius() const;
    
    //返回胶囊的实际高度
		float GetHeight() const;

	private:
		void CreateCollisionShape(float p_radius, float p_height);
		void RecreateCollisionShape(float p_radius, float p_height);
		virtual void SetLocalScaling(const GeMaths::FVector3& p_scaling) override;

	private:
		float m_radius;
		float m_height;
	};
}

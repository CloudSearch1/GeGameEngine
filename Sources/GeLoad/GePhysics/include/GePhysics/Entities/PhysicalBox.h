#pragma once

#include "GePhysics/Entities/PhysicalObject.h"

namespace GePhysics::Entities
{
  //具有盒子形状的物理对象
	class PhysicalBox : public PhysicalObject
	{
	public:

    //PhysicalBox 构造函数（外部转换管理）
		PhysicalBox(const GeMaths::FVector3& p_size = {0.5f, 0.5f, 0.5f});

    //PhysicalBox 构造函数（外部转换管理）
		PhysicalBox(GeMaths::FTransform& p_transform, const GeMaths::FVector3& p_size = { 0.5f, 0.5f, 0.5f });

    //定义物理框的大小
		void SetSize(const GeMaths::FVector3& p_size);

    //返回实体框的大小
		GeMaths::FVector3 GetSize() const;

	private:
		void CreateCollisionShape(const GeMaths::FVector3& p_size);
		void RecreateCollisionShape(const GeMaths::FVector3& p_size);
		virtual void SetLocalScaling(const GeMaths::FVector3& p_scaling) override;

	private:
		GeMaths::FVector3 m_size;
	};
}

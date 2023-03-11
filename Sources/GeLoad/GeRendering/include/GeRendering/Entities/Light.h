#pragma once

#include <GeMaths/FVector3.h>
#include <GeMaths/FMatrix4.h>
#include <GeMaths/FTransform.h>


namespace GeRendering::Entities
{
	//包含light各项属性的结构体
	struct Light
	{
		//灯光类型的枚举
		enum class Type
    {
      POINT,
      DIRECTIONAL,
      SPOT,
      AMBIENT_BOX,
      AMBIENT_SPHERE
    };

		Light(GeMaths::FTransform& p_tranform, Type p_type);

    //生成光矩阵，准备发送给 GPU
		GeMaths::FMatrix4 GenerateMatrix() const;

    //根据二次衰减方程计算光照影响发范围
		float GetEffectRange() const;

		//返回光照的Transform
		const GeMaths::FTransform& GetTransform() const;

		GeMaths::FVector3	color = { 1.f, 1.f, 1.f };
		float intensity	  = 1.f;
		float constant	  = 0.0f;
		float linear		  = 0.0f;
		float quadratic	  = 1.0f;
		float cutoff		  = 12.f;
		float outerCutoff = 15.f;
		float type		    = 0.0f;

	protected:
		GeMaths::FTransform& m_transform;
	};
}

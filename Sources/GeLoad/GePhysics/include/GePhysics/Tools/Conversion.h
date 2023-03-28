#pragma once

#include <bullet/btBulletCollisionCommon.h>

#include <GeMaths/FTransform.h>
#include <GeMaths/FVector3.h>
#include <GeMaths/FQuaternion.h>

namespace GePhysics::Tools
{
  //将子弹数学转换为 GeMaths 的转换助手
	class Conversion
	{
	public:
		Conversion() = delete;
    
    //将 FTransform 转换为 btTransform
		static btTransform ToBtTransform(const GeMaths::FTransform& p_transform);
    
    //将 FVector3 转换为 btVector3
		static btVector3 ToBtVector3(const GeMaths::FVector3& p_vector);

    //将 FQuaternion 转换为 btQuaternion
		static btQuaternion ToBtQuaternion(const GeMaths::FQuaternion& p_quaternion);

    //将 btTransform 转换为 FTransform
		static GeMaths::FTransform ToOvTransform(const btTransform& p_transform);
    
    //将 btVector3 转换为 FVector3
		static GeMaths::FVector3 ToOvVector3(const btVector3& p_vector);
    
    //将 btQuaternion 转换为 FQuaternion
		static GeMaths::FQuaternion ToOvQuaternion(const btQuaternion& p_quaternion);
	};
}

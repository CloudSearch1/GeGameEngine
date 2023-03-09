#pragma once

#include "GeMaths/FVector3.h"
#include "GeMaths/FMatrix3.h"
#include "GeMaths/FMatrix4.h"

#include <string>

namespace GeMaths
{
  //具有浮点精度的四元数的数学表示
	struct FQuaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

    //返回一个身份四元数
		static const FQuaternion Identity;

    //默认四元数构造函数（创建一个以 1 为 w 的恒等四元数）
		FQuaternion();

    //创建一个具有定义实数值的恒等四元数
		FQuaternion(float p_real);

    //从一组 4 个浮点数 (x, y, z, w) 创建一个四元数
		FQuaternion(float p_x, float p_y, float p_z, float p_w);

    //拷贝构造函数
		FQuaternion(const FQuaternion& p_other);

    //从旋转矩阵构造
		FQuaternion(const FMatrix3& p_rotationMatrix);

    //从旋转矩阵构造
		FQuaternion(const FMatrix4& p_rotationMatrix);

    //从欧拉角构造
		FQuaternion(const FVector3& p_euler);

    //从向前和向上向量创建一个四元数
		static FQuaternion LookAt(const FVector3& p_forward, const FVector3& p_up);

    //检查四元数是否为恒等式
		static bool IsIdentity(const FQuaternion& p_target);

    //检查四元数是否纯
		static bool IsPure(const FQuaternion& p_target);

    //检查四元数是否归一化
		static bool IsNormalized(const FQuaternion& p_target);

    //计算两个四元数之间的点积
		static float DotProduct(const FQuaternion& p_left, const FQuaternion& p_right);	

    //计算四元数的归一化
		static FQuaternion Normalize(const FQuaternion& p_target);

    //计算四元数的长度
		static float Length(const FQuaternion& p_target);

    //计算四元数的长度平方
		static float LengthSquare(const FQuaternion& p_target);

    //返回四元数的角度
		static float GetAngle(const FQuaternion& p_target);

    //返回给定四元数的旋转轴
		static FVector3 GetRotationAxis(const FQuaternion& p_target);

    //计算四元数的倒数
		static FQuaternion Inverse(const FQuaternion& p_target);

    //计算四元数的共轭
		static FQuaternion Conjugate(const FQuaternion& p_target);

    //计算四元数的平方
		static FQuaternion Square(const FQuaternion& p_target);

    //从四元数中获取轴和角度
		static std::pair<FVector3, float> GetAxisAndAngle(const FQuaternion& p_target);

    //计算两个四元数之间的角度。
		static float AngularDistance(const FQuaternion& p_left, const FQuaternion& p_right);

    //Lerp 两个四元数
		static FQuaternion Lerp(const FQuaternion& p_start, const FQuaternion& p_end, float p_alpha);

    //Slerp 两个四元数
		static FQuaternion Slerp(const FQuaternion& p_start, const FQuaternion& p_end, float p_alpha);

    //Nlerp 两个四元数（= Lerp + 归一化）
		static FQuaternion Nlerp(const FQuaternion& p_start, const FQuaternion& p_end, float p_alpha);

    //使用旋转四元数旋转一个点(qpq^-1)
		static FVector3 RotatePoint(const FVector3& p_point, const FQuaternion& p_quaternion);

    //使用旋转四元数围绕轴心点旋转一个点
		static FVector3 RotatePoint(const FVector3& p_point, const FQuaternion& p_quaternion, const FVector3& p_pivot);

    //返回每个轴的欧拉轴角度（以度为单位）。
		static FVector3 EulerAngles(const FQuaternion& p_target);

    //从给定的四元数中返回一个旋转矩阵 (3x3)
		static FMatrix3 ToMatrix3(const FQuaternion& p_target);

    //从给定的四元数中返回一个旋转矩阵 (4x4)
		static FMatrix4 ToMatrix4(const FQuaternion& p_target);

		bool operator==(const FQuaternion& p_otherQuat) const;
		bool operator!=(const FQuaternion& p_otherQuat) const;
		FQuaternion operator+(const FQuaternion& p_otherQuat) const;
		FQuaternion& operator+=(const FQuaternion& p_otherQuat);
		FQuaternion operator-(const FQuaternion& p_otherQuat) const;
		FQuaternion& operator-=(const FQuaternion& p_otherQuat);
		float operator|(const FQuaternion& p_otherQuat) const;
		FQuaternion& operator*=(const float p_scale);
		FQuaternion operator*(const float p_scale) const;
		FQuaternion operator*(const FQuaternion& p_otherQuat) const;
		FQuaternion& operator*=(const FQuaternion& p_otherQuat);
		FVector3 operator*(const FVector3& p_toMultiply) const;
		FMatrix3 operator*(const FMatrix3& p_multiply) const;
		FQuaternion& operator/=(const float p_scale);
		FQuaternion operator/(const float p_scale) const;
	};
}

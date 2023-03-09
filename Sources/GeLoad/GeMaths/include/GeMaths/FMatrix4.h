#pragma once

// TODO: Move constants to cpp
#define PI 3.14159265359f
#define EPSILON 0.00001f

#include <stdint.h>

#include "GeMaths/FVector3.h"
#include "GeMaths/FVector4.h"


namespace GeMaths
{

	struct FQuaternion;
  
  //4x4 浮点矩阵的数学表示
	struct FMatrix4
	{
		float data[16];
		static const FMatrix4 Identity;

		FMatrix4();

		FMatrix4(float p_element1, float p_element2, float p_element3,
				 float p_element4, float p_element5, float p_element6,
				 float p_element7, float p_element8, float p_element9,
			     float p_element10, float p_element11, float p_element12, 
				 float p_element13, float p_element14, float p_element15, float p_element16);

    //拷贝构造函数
		FMatrix4(const FMatrix4& p_other);

    //Copy assignment
		FMatrix4& operator=(const FMatrix4& p_other);
    
    //检查元素是否相等
		bool operator==(const FMatrix4& p_other);

    //逐元素加法
		FMatrix4 operator+(const FMatrix4& p_other) const;
    
    //逐元素加法
		FMatrix4& operator+=(const FMatrix4& p_other);

    //逐元素减法
		FMatrix4 operator-(float p_scalar) const;

    //逐元素减法
		FMatrix4 operator-(const FMatrix4& p_other) const;

    //逐元素减法
		FMatrix4& operator-=(const FMatrix4& p_other);

    //标量积
		FMatrix4 operator*(float p_scalar) const;

    //标量积
		FMatrix4& operator*=(float p_scalar);

    //标量积
    FVector4 operator*(const FVector4& p_vector) const;

    //矩阵积
		FMatrix4 operator*(const FMatrix4& p_other) const;

    //矩阵积
    FMatrix4& operator*=(const FMatrix4& p_other);

    //标量除法
		FMatrix4 operator/(float p_scalar) const;

    //标量除法
		FMatrix4& operator/=(float p_scalar);

    //矩阵除法
		FMatrix4 operator/(const FMatrix4& p_other) const;

    //矩阵除法
		FMatrix4& operator/=(const FMatrix4& p_other);

    //获取索引处的元素（行，列）
		float& operator()(uint8_t p_row, uint8_t p_column);

    //检查元素是否相等
		static bool AreEquals(const FMatrix4& p_left, const FMatrix4& p_right);

    //逐元素加法
		static FMatrix4 Add(const FMatrix4& p_left, float p_scalar);

    //逐元素加法
		static FMatrix4 Add(const FMatrix4& p_left, const FMatrix4& p_right);

    //逐元素减法
		static FMatrix4 Subtract(const FMatrix4& p_left, float p_scalar);

    //逐元素减法
		static FMatrix4 Subtract(const FMatrix4& p_left, const FMatrix4& p_right);

    //标量积
		static FMatrix4 Multiply(const FMatrix4& p_left, float p_scalar);

    //矢量积
		static FVector4 Multiply(const FMatrix4& p_matrix, const FVector4& p_vector);

    //矩阵乘积
		static FMatrix4 Multiply(const FMatrix4& p_left, const FMatrix4& p_right);

    //标量除法
		static FMatrix4 Divide(const FMatrix4& p_left, float p_scalar);

    //矩阵师,除法
		static FMatrix4 Divide(const FMatrix4& p_left, const FMatrix4& p_right);

    //与单位矩阵比较
		static bool IsIdentity(const FMatrix4& p_matrix);

    //返回矩阵的次要
		static float GetMinor(float p_minor0, float p_minor1, float p_minor2, 
							  float p_minor3, float p_minor4, float p_minor5,
							  float p_minor6, float p_minor7, float p_minor8);

    //计算矩阵行列式
		static float Determinant(const FMatrix4& p_matrix);

    //返回转置矩阵
		static FMatrix4 Transpose(const FMatrix4& p_matrix);

    //返回逆矩阵
		static FMatrix4 Inverse(const FMatrix4& p_matrix);

    //返回 3D 平移矩阵
		static FMatrix4 Translation(const FVector3& p_translation);

    //在 3D 中转换矩阵
		static FMatrix4 Translate(const FMatrix4& p_matrix, const FVector3& p_translation);

    //返回 X 轴上的 3D 旋转矩阵
		static FMatrix4 RotationOnAxisX(float p_rotation);

    //在 X 轴上以 3D 方式旋转矩阵
		static FMatrix4 RotateOnAxisX(const FMatrix4& p_matrix, float p_rotation);

    //在 Y 轴上以 3D 方式旋转矩阵
		static FMatrix4 RotationOnAxisY(float p_rotation);
		
    //在 Y 轴上以 3D 方式旋转矩阵
		static FMatrix4 RotateOnAxisY(const FMatrix4& p_matrix, float p_rotation);
    
    //返回 Z 轴上的 3D 旋转矩阵
		static FMatrix4 RotationOnAxisZ(float p_rotation);

    //在 Z 轴上以 3D 方式旋转矩阵
		static FMatrix4 RotateOnAxisZ(const FMatrix4& p_matrix, float p_rotation);

    //返回 XYZ 轴上的 3D 旋转矩阵
		static FMatrix4 RotationYXZ(float p_rotation);

    //在 XYZ 轴上以 3D 方式旋转矩阵
		static FMatrix4 RotateYXZ(const FMatrix4& p_matrix, float p_rotation);

    //返回 3D 缩放矩阵
		static FMatrix4 Scaling(const FVector3& p_scale);

    //3D 比例矩阵
		static FMatrix4 Scale(const FMatrix4& p_matrix, const FVector3& p_scale);

    //从四元数返回旋转矩阵
		static FMatrix4 Rotation(const FQuaternion& p_quaternion);

    //返回四元数的 3D 旋转矩阵
		static FMatrix4 Rotate(const FMatrix4& p_matrix, const FQuaternion& p_quaternion);

    //返回透视矩阵
		static FMatrix4 CreatePerspective(const float p_fov, const float p_aspectRatio, const float p_zNear, const float p_zFar);

    //返回一个正交矩阵
    static FMatrix4 CreateOrthographic(const float p_size, const float p_aspectRatio, const float p_zNear, const float p_zFar);

    //返回视图矩阵
		static FMatrix4 CreateView(const float p_eyeX, const float p_eyeY, const float p_eyeZ, const float p_lookX, const float p_lookY, const float p_lookZ, const float p_upX, const float p_upY, const float p_upZ);
		
    //返回平截头体矩阵
		static FMatrix4 CreateFrustum(const float p_left, const float p_right, const float p_bottom, const float p_top, const float p_zNear, const float p_zFar);

    //获取行
		static FVector4 GetRow(const FMatrix4& p_matrix, uint8_t p_row);

    //获取列
		static FVector4 GetColumn(const FMatrix4& p_matrix, uint8_t p_column);
	};
}

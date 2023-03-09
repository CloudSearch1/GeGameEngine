#pragma once

#include <stdint.h>

#include "GeMaths/FVector3.h"
#include "GeMaths/FVector2.h"

namespace GeMaths
{
  //3x3 浮点矩阵的数学表示
	struct FMatrix3
	{
		float data[9];
		static const FMatrix3 Identity;

		FMatrix3();

    //将所有元素设置为值
		FMatrix3(float p_value);

		FMatrix3(float p_element1, float p_element2, float p_element3,
				 float p_element4, float p_element5, float p_element6, 
				 float p_element7, float p_element8, float p_element9);

    //拷贝构造函数
		FMatrix3(const FMatrix3& p_other);

		FMatrix3& operator=(const FMatrix3& p_other);

    //检查元素是否相等
		bool operator==(const FMatrix3& p_other);

    //逐元素加法
		FMatrix3 operator+(const FMatrix3& p_other) const;

    //逐元素加法
		FMatrix3& operator+=(const FMatrix3& p_other);

    //逐元素减法
		FMatrix3 operator-(const FMatrix3& p_other) const;

    //逐元素减法
		FMatrix3& operator-=(const FMatrix3& p_other);

    //标量积
		FMatrix3 operator*(float p_scalar) const;
    
    //标量积
		FMatrix3& operator*=(float p_scalar);

    //矢量乘积
		FVector3 operator*(const FVector3& p_vector) const;

    //矩阵乘积
		FMatrix3 operator*(const FMatrix3& p_other) const;

    //矩阵乘积
		FMatrix3& operator*=(const FMatrix3& p_other);

    //标量除法
		FMatrix3 operator/(float p_scalar) const;

    //标量除法
		FMatrix3& operator/=(float p_scalar);

    //矩阵师
		FMatrix3 operator/(const FMatrix3& p_other) const;

    //矩阵师
		FMatrix3& operator/=(const FMatrix3& p_other);

    //获取索引处的元素（行，列）
		float& operator()(uint8_t p_row, uint8_t p_column);
		
    //检查元素是否相等
		static bool AreEquals(const FMatrix3& p_left, const FMatrix3& p_right);

    //逐元素加法
		static FMatrix3 Add(const FMatrix3& p_left, float p_scalar);

    //逐元素减法
		static FMatrix3 Add(const FMatrix3& p_left, const FMatrix3& p_right);

    //逐元素减法
		static FMatrix3 Subtract(const FMatrix3& p_left, float p_scalar);

    //逐元素减法
		static FMatrix3 Subtract(const FMatrix3& p_left, const FMatrix3& p_right);

    //标量积
		static FMatrix3 Multiply(const FMatrix3& p_left, float p_scalar);

    //矢量乘积
		static FVector3 Multiply(const FMatrix3& p_matrix, const FVector3& p_vector);

    //矩阵乘积
    static FMatrix3 Multiply(const FMatrix3& p_left, const FMatrix3& p_right);

    //标量除法
		static FMatrix3 Divide(const FMatrix3& p_left, float p_scalar);

    //矩阵师
		static FMatrix3 Divide(const FMatrix3& p_left, const FMatrix3& p_right);

    //与单位矩阵比较
		static bool IsIdentity(const FMatrix3& p_matrix);

    //计算矩阵行列式
		static float Determinant(const FMatrix3& p_matrix);

    //返回转置矩阵
		static FMatrix3 Transpose(const FMatrix3& p_matrix);

    //返回辅因子矩阵
		static FMatrix3 Cofactor(const FMatrix3& p_matrix);

    //返回小矩阵
		static FMatrix3 Minor(const FMatrix3& p_matrix);

    //返回伴随矩阵
		static FMatrix3 Adjoint(const FMatrix3& p_other);

    //返回逆矩阵
		static FMatrix3 Inverse(const FMatrix3& p_matrix);

    //返回二维平移矩阵
		static FMatrix3 Translation(const FVector2& p_translation);

    //在 2D 中转换矩阵
		static FMatrix3 Translate(const FMatrix3& p_matrix, const FVector2& p_translation);
    
    //返回二维旋转矩阵
		static FMatrix3 Rotation(float p_rotation);
    
    //二维旋转矩阵
		static FMatrix3 Rotate(const FMatrix3& p_matrix, float p_rotation);
    
    //返回二维缩放矩阵c
		static FMatrix3 Scaling(const FVector2& p_scale);

    //二维比例矩阵
		static FMatrix3 Scale(const FMatrix3& p_matrix, const FVector2& p_scale);
	
    //获取行
		static FVector3 GetRow(const FMatrix3& p_matrix, uint8_t p_row);

    //获取列
		static FVector3 GetColumn(const FMatrix3& p_matrix, uint8_t p_column);
	};
}

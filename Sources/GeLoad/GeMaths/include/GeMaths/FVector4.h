#pragma once


namespace GeMaths
{
  //4D 浮点向量的数学表示
	struct FVector4
	{
		static const FVector4 One;
		static const FVector4 Zero;

		float x;
		float y;
		float z;
		float w;

    //默认构造函数
		FVector4(float p_x = 0.0f, float p_y = 0.0f, float p_z = 0.0f, float p_w = 0.0f);

    //拷贝构造函数
		FVector4(const FVector4& p_toCopy);

    //移动构造函数
		FVector4(FVector4&& p_toMove) noexcept = default;

    //逻辑否定
		FVector4 operator-() const;

    //拷贝赋值运算
		FVector4 operator=(const FVector4& p_other);

    //计算两个向量的和
		FVector4 operator+(const FVector4& p_other) const;

    //将右向量添加到左向量
		FVector4& operator+=(const FVector4& p_other);

    //计算两个向量的减法
		FVector4 operator-(const FVector4& p_other) const;

    //从左边的向量中移除右边的向量
		FVector4& operator-=(const FVector4& p_other);

    //计算向量与标量的乘积
		FVector4 operator*(float p_scalar) const;

    //将向量乘以标量
		FVector4& operator*=(float p_scalar);

    //返回标量和实际向量的除法
		FVector4 operator/(float p_scalar) const;

    //将标量除以实际向量
		FVector4& operator/=(float p_scalar);

    //如果两个向量相等则返回真
		bool operator==(const FVector4& p_other);

    //如果两个向量不同则返回真
		bool operator!=(const FVector4& p_other);

    //计算两个向量的和
		static FVector4 Add(const FVector4& p_left, const FVector4& p_right);

    //计算两个向量的减法
		static FVector4 Substract(const FVector4& p_left, const FVector4& p_right);

    //计算向量与标量的乘积
		static FVector4 Multiply(const FVector4& p_target, float p_scalar);

    //将标量除以向量左
		static FVector4 Divide(const FVector4& p_left, float p_scalar);

    //返回向量的长度
		static float Length(const FVector4& p_target);

    //返回两个向量的点积
		static float Dot(const FVector4& p_left, const FVector4& p_right);

    //返回给定向量的归一化
		static FVector4 Normalize(const FVector4& p_target);

    //计算两个向量之间的插值
		static FVector4 Lerp(const FVector4& p_start, const FVector4& p_end, float p_alpha);
	};
}

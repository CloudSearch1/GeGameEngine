#pragma once


namespace GeMaths
{
  //二维浮点向量的数学表示
	struct FVector2
	{
		static const FVector2 One;
		static const FVector2 Zero;

		float x;
		float y;

    //默认构造函数
		FVector2(float p_x = 0.0f, float p_y = 0.0f);

    //默认构造函数
		FVector2(const FVector2& p_toCopy);

    //移动构造函数
		FVector2(FVector2&& p_toMove) noexcept = default;

    //Negation
		FVector2 operator-() const;

    //复制作业
		FVector2 operator=(const FVector2& p_other);

    //计算两个向量的和
		FVector2 operator+(const FVector2& p_other) const;

    //将右向量添加到左向量
		FVector2& operator+=(const FVector2& p_other);

    //计算两个向量的减法
		FVector2 operator-(const FVector2& p_other) const;

    //从左边的向量中移除右边的向量
		FVector2& operator-=(const FVector2& p_other);

    //计算向量与标量的乘积
		FVector2 operator*(float p_scalar) const;

    //将向量乘以标量
		FVector2& operator*=(float p_scalar);

    //返回标量和实际向量的除法
		FVector2 operator/(float p_scalar) const;

    //将标量除以实际向量
		FVector2& operator/=(float p_scalar);

    //如果两个向量相等则返回真
		bool operator==(const FVector2& p_other);

    //如果两个向量不同则返回真
		bool operator!=(const FVector2& p_other);

    //计算两个向量的和
		static FVector2 Add(const FVector2& p_left, const FVector2& p_right);

    //计算两个向量的减法
		static FVector2 Substract(const FVector2& p_left, const FVector2& p_right);

    //计算向量与标量的乘积
		static FVector2 Multiply(const FVector2& p_target, float p_scalar);

    //将标量除以向量左
		static FVector2 Divide(const FVector2& p_left, float p_scalar);

    //返回向量的长度
		static float Length(const FVector2& p_target);

    //返回两个向量的点积
		static float Dot(const FVector2& p_left, const FVector2& p_right);

    //返回给定向量的归一化
		static FVector2 Normalize(const FVector2& p_target);

    //计算两个向量之间的插值
		static FVector2 Lerp(const FVector2& p_start, const FVector2& p_end, float p_alpha);

    //计算两个向量之间的夹角
		static float AngleBetween(const FVector2& p_from, const FVector2& p_to);
	};
}

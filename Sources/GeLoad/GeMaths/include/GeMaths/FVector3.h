#pragma once


namespace GeMaths
{
  //浮点数的 3D 向量的数学表示
	struct FVector3
	{
		static const FVector3 One;
		static const FVector3 Zero;
		static const FVector3 Forward;
		static const FVector3 Right;
		static const FVector3 Up;

		float x;
		float y;
		float z;

    //默认构造函数
		FVector3(float p_x = 0.0f, float p_y = 0.0f, float p_z = 0.0f);

    //拷贝构造函数
		FVector3(const FVector3& p_toCopy);

    //移动构造函数
		FVector3(FVector3&& p_toMove) noexcept = default;

    //否定
		FVector3 operator-() const;

    //拷贝赋值运算符
		FVector3 operator=(const FVector3& p_other);

    //计算两个向量的和
		FVector3 operator+(const FVector3& p_other) const;

    //将右向量添加到左向量
		FVector3& operator+=(const FVector3& p_other);

    //计算两个向量的减法
		FVector3 operator-(const FVector3& p_other) const;

    //从左边的向量中移除右边的向量
		FVector3& operator-=(const FVector3& p_other);

    //计算向量与标量的乘积
		FVector3 operator*(float p_scalar) const;

    //将向量乘以标量
		FVector3& operator*=(float p_scalar);

    //返回标量和实际向量的除法
		FVector3 operator/(float p_scalar) const;

    //将标量除以实际向量
		FVector3& operator/=(float p_scalar);

    //如果两个向量相等则返回真
		bool operator==(const FVector3& p_other);

    //如果两个向量不同则返回真
		bool operator!=(const FVector3& p_other);

    //计算两个向量的和
		static FVector3 Add(const FVector3& p_left, const FVector3& p_right);

    //计算两个向量的减法
		static FVector3 Substract(const FVector3& p_left, const FVector3& p_right);

    //计算向量与标量的乘积
		static FVector3 Multiply(const FVector3& p_target, float p_scalar);

    //将标量除以向量左
		static FVector3 Divide(const FVector3& p_left, float p_scalar);

    //返回向量的长度
		static float Length(const FVector3& p_target);

    //返回两个向量的点积
		static float Dot(const FVector3& p_left, const FVector3& p_right);

    //返回两个向量之间的距离
		static float Distance(const FVector3& p_left, const FVector3& p_right);

    //返回两个向量的叉积
		static FVector3 Cross(const FVector3& p_left, const FVector3& p_right);

    //返回给定向量的归一化
		static FVector3 Normalize(const FVector3& p_target);

    //计算两个向量之间的插值
		static FVector3 Lerp(const FVector3& p_start, const FVector3& p_end, float p_alpha);

    //计算两个向量之间的夹角
		static float AngleBetween(const FVector3& p_from, const FVector3& p_to);
	};
}

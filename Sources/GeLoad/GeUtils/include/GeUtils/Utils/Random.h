#pragma once

#include <random>

namespace GeUtils::Utils
{
  //处理随机数生成
  class Random
  {
  public:
    Random() = delete;

    //在两个给定整数之间生成一个随机数（闭区间）
    static int Generate(int p_min, int p_max);

    //在两个给定的浮点数之间生成一个随机数（闭区间）
    static float Generate(float p_min, float p_max);

    //验证百分比是否满足
    static bool CheckPercentage(float p_percentage);

  private:
    static std::default_random_engine __GENERATOR;
  };
}

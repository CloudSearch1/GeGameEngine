#include "GeUtils/Utils/Random.h"

namespace GeUtils::Utils
{

  std::default_random_engine Random::__GENERATOR;

  int Random::Generate(int p_min, int p_max)
  {
    std::uniform_int_distribution<int> distribution(p_min, p_max);
    return distribution(__GENERATOR);
  }

  float Random::Generate(float p_min, float p_max)
  {
    std::uniform_real_distribution<float> distribution(p_min, p_max);
    return distribution(__GENERATOR);
  }

  bool Random::CheckPercentage(float p_percentage)
  {
    std::uniform_real_distribution<float> distribution(0.0f, 100.0f);
    return distribution(__GENERATOR) <= p_percentage;
  }

}

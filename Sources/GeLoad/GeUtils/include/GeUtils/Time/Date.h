#pragma once

#include <string>

namespace GeUtils::Time
{
  class Date
  {
  public:
    Date() = delete;

    static std::string GetDate();
  };
}

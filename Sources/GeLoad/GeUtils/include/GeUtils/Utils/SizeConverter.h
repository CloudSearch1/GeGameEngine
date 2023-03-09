#pragma once

#include <cstdint>
#include <tuple>
#include <string>


namespace GeUtils::Utils
{
    //处理大小转换
    class SizeConverter
    {
    public:
        enum class ESizeUnit
        {
            BYTE        = 0,
            KILO_BYTE   = 3,
            MEGA_BYTE   = 6,
            GIGA_BYTE   = 9,
            TERA_BYTE   = 12
        };

        //禁止构造函数
        SizeConverter() = delete;

        //将给定大小转换为最佳单位以避免大数字（例如：1000B 将返回 1KB）
        static std::pair<float, ESizeUnit> ConvertToOptimalUnit(float p_value, ESizeUnit p_unit);

        //将给定大小从一个单位转换为另一个单位
        static float Convert(float p_value, ESizeUnit p_from, ESizeUnit p_to);

        //将给定单位转换为字符串
        static std::string UnitToString(ESizeUnit p_unit);
    };
}

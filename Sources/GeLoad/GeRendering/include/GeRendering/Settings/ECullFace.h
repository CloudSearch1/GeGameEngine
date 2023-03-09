#pragma once



namespace GeRendering::Settings
{
  //OpenGL剔除面枚举
  enum class ECullFace
  {
    FRONT			      = 0x0404,
    BACK			      = 0x0405,
    FRONT_AND_BACK	= 0x0408
  };
}

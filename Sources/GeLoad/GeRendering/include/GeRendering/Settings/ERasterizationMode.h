#pragma once



namespace GeRendering::Settings
{
  //OpenGL 光栅化模式枚举
	enum class ERasterizationMode
	{
		POINT	= 0x1B00,
		LINE	= 0x1B01,
		FILL	= 0x1B02
	};
}

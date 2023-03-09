#pragma once

#include <stdint.h>


#include "GeRendering/Settings/DriverSettings.h"

namespace GeRendering::Context
{
  //OpenGL上下文
	class Driver
	{
	public:
		//创建OpenGL上下文
		Driver(const Settings::DriverSettings& p_driverSettings);
		~Driver() = default;

    //返回OpenGL上下文是否处于活跃状态
		bool IsActive() const;

	private:
		void InitGlew();
    //返回gl程序状态信息
		static void __stdcall GLDebugMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParam);

	private:
		bool m_isActive;
	};
}

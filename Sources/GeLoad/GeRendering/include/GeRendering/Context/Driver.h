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

	private:
		bool m_isActive;
	};
}

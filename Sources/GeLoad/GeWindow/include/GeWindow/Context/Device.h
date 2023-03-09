#pragma once

#include <unordered_map>

#include <GLFW/glfw3.h>

#include <GeUtils/Eventing/Event.h>

#include "GeWindow/Context/EDeviceError.h"
#include "GeWindow/Settings/DeviceSettings.h"
#include "GeWindow/Cursor/ECursorShape.h"

namespace GeWindow::Context
{
  //Device 表示窗口上下文。 有必要创建一个设备
  //创建
	class Device
	{
	public:
    //绑定一个侦听器到这个事件来接收设备错误
		static GeUtils::Eventing::Event<EDeviceError, std::string> ErrorEvent;

    //设备的构造函数将负责 GLFW 初始化
		Device(const Settings::DeviceSettings& p_deviceSettings);

    //设备的析构函数将负责 GLFW 的销毁
		~Device();

    //返回主要 monity 的大小（以像素为单位）
		std::pair<int16_t, int16_t> GetMonitorSize() const;

    //返回对应于给定形状的 GLFWcursor 实例
		GLFWcursor* GetCursorInstance(Cursor::ECursorShape p_cursorShape) const;

    //如果当前启用了 vsync，则返回 true
		bool HasVsync() const;

    //启用或禁用垂直同步
    //必须在创建一个窗口并将其定义为当前上下文后调用此方法
		void SetVsync(bool p_value);

    //使用创建的窗口启用输入和事件管理
    //应该每帧调用一次
		void PollEvents() const;

    //返回设备启动后经过的时间
		float GetElapsedTime() const;

	private:
		void BindErrorCallback();
		void CreateCursors();
		void DestroyCursors();

	private:
		bool m_vsync = true;
		bool m_isAlive = false;
		std::unordered_map<Cursor::ECursorShape, GLFWcursor*> m_cursors;
	};
}

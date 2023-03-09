#pragma once

#include <string>

#include "GeWindow/Cursor/ECursorShape.h"
#include "GeWindow/Cursor/ECursorMode.h"

namespace GeWindow::Settings
{
	//包含窗口设置
	struct WindowSettings 
	{
		//用于忽略值设置的简单常量（让程序为您决定）
		//note 你可以只在指定的地方使用 WindowSettings::DontCare
		static const int32_t DontCare = -1;

		//窗口标题（显示在标题栏中）
		std::string title;

		//窗口的像素宽度
		uint16_t width;
		
		//窗口的高度（以像素为单位）
		uint16_t height;

		//窗口的最小宽度。
		//使用 WindowSettings::DontCare 禁用限制
		int16_t minimumWidth = DontCare;

		//窗口的最小高度。
		int16_t minimumHeight = DontCare;

		//窗口的最大宽度。
		int16_t maximumWidth = DontCare;

		//窗口的最大高度。
		int16_t maximumHeight = DontCare;

		//指定窗口默认是全屏模式还是窗口模式
		bool fullscreen = false;

		//指定窗口模式窗口是否具有窗口装饰，例如边框、关闭小部件等。未装饰的窗口可能仍允许用户在某些平台上生成关闭事件。
		bool decorated = true;

		//指定窗口模式窗口是否可以由用户调整大小。 窗口仍可使用调整大小“Window”类的“SetSize(uint16_t, uint16_t)”方法
		bool resizable = true;

		//指定窗口模式窗口在创建时是否将获得输入焦点。 此提示被忽略全屏和最初隐藏的窗口。
		bool focused = true;

		//指定窗口模式窗口在创建时是否最大化。 对于全屏窗口，此提示将被忽略。
		bool maximized = false;

		//指定窗口模式窗口是否将浮动在其他常规窗口之上，也称为最顶层或始终位于最顶层。
		bool floating = false;

		//指定窗口模式窗口最初是否可见。 对于全屏窗口，此提示将被忽略。
		bool visible = true;

		//指定全屏窗口是否会自动图标化和恢复
		bool autoIconify = true;

		//指定全屏窗口所需的刷新率.
		int32_t refreshRate = WindowSettings::DontCare;

		//指定窗口的默认光标模式
		Cursor::ECursorMode cursorMode = Cursor::ECursorMode::NORMAL;

		//指定窗口的默认光标形状
		Cursor::ECursorShape cursorShape = Cursor::ECursorShape::ARROW;

		//定义要使用的样本数（用于抗锯齿）
		uint32_t samples = 4;
	};
}

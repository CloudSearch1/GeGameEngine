#pragma once

#include <unordered_map>

#include "GeWindow/Window.h"
#include "GeWindow/Inputs/EKey.h"
#include "GeWindow/Inputs/EKeyState.h"
#include "GeWindow/Inputs/EMouseButton.h"
#include "GeWindow/Inputs/EMouseButtonState.h"

namespace GeWindow::Inputs
{
  //处理输入（鼠标和键盘）
	class InputManager
	{
	public:
		InputManager(Window& p_window);

    //通过删除窗口上的侦听器来销毁输入管理器
		~InputManager();

    //返回给定键的当前状态
		EKeyState GetKeyState(EKey p_key) const;

    //返回给定鼠标按钮的当前状态
		EMouseButtonState GetMouseButtonState(EMouseButton p_button) const;

    //如果在帧期间按下了给定的键，则返回 true
		bool IsKeyPressed(EKey p_key) const;

    //如果给定的键在帧中被释放则返回真
		bool IsKeyReleased(EKey p_key) const;

    //如果在帧期间按下了给定的鼠标按钮，则返回 true
		bool IsMouseButtonPressed(EMouseButton p_button) const;

    //如果给定的鼠标按钮在帧期间已被释放，则返回 true
		bool IsMouseButtonReleased(EMouseButton p_button) const;

    //返回当前鼠标相对于窗口的位置
		std::pair<double, double> GetMousePosition() const;

    //清除任何发生的事件
    //应该在每个游戏滴答结束时调用
		void ClearEvents();

	private:
		void OnKeyPressed(int p_key);
		void OnKeyReleased(int p_key);
		void OnMouseButtonPressed(int p_button);
		void OnMouseButtonReleased(int p_button);

	private:
		Window& m_window;

		GeUtils::Eventing::ListenerID m_keyPressedListener;
		GeUtils::Eventing::ListenerID m_keyReleasedListener;
		GeUtils::Eventing::ListenerID m_mouseButtonPressedListener;
		GeUtils::Eventing::ListenerID m_mouseButtonReleasedListener;

		std::unordered_map<EKey, EKeyState> m_keyEvents;
		std::unordered_map<EMouseButton, EMouseButtonState>	m_mouseButtonEvents;
	};
}

#pragma once

#include <string>

#include <GLFW/glfw3.h>

#include "GeWindow/Context/Device.h"
#include "GeWindow/Settings/WindowSettings.h"
#include "GeWindow/Cursor/ECursorShape.h"
#include "GeWindow/Cursor/ECursorMode.h"

namespace GeWindow
{
  //一个简单的基于操作系统的窗口
  class Window
  {
  public:
    GeUtils::Eventing::Event<int> KeyPressedEvent;
    GeUtils::Eventing::Event<int> KeyReleasedEvent;
    GeUtils::Eventing::Event<int> MouseButtonPressedEvent;
    GeUtils::Eventing::Event<int> MouseButtonReleasedEvent;

    GeUtils::Eventing::Event<uint16_t, uint16_t> ResizeEvent;
    GeUtils::Eventing::Event<uint16_t, uint16_t> FramebufferResizeEvent;
    GeUtils::Eventing::Event<int16_t, int16_t> MoveEvent;
    GeUtils::Eventing::Event<int16_t, int16_t> CursorMoveEvent;
    GeUtils::Eventing::Event<> MinimizeEvent;
    GeUtils::Eventing::Event<> MaximizeEvent;
    GeUtils::Eventing::Event<> GainFocusEvent;
    GeUtils::Eventing::Event<> LostFocusEvent;
    GeUtils::Eventing::Event<> CloseEvent;

    Window(const Context::Device& p_device, const Settings::WindowSettings& p_windowSettings);
    ~Window();

    void SetIcon(const std::string& p_filePath);

    //从内存中设置图标
    void SetIconFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height);

    //查找具有给定 GLFWwindow 的窗口实例
    static Window* FindInstance(GLFWwindow* p_glfwWindow);

    //调整窗口大小
    void SetSize(uint16_t p_width, uint16_t p_height);

    //定义窗口的最小尺寸
    void SetMinimumSize(int16_t p_minimumWidth, int16_t p_minimumHeight);

    //定义窗口的最大尺寸
    void SetMaximumSize(int16_t p_maximumWidth, int16_t p_maximumHeight);

    //定义窗口的位置
    void SetPosition(int16_t p_x, int16_t p_y);

    //最小化窗口
    void Minimize() const;

    //最大化窗口
    void Maximize() const;

    //恢复窗口
    void Restore() const;

    //隐藏指定的窗口，如果它以前是可见的
    void Hide() const;

    //显示指定的窗口，如果它以前是隐藏的
    void Show() const;

    //聚焦窗口
    void Focus() const;

    //将窗口的应该关闭标志设置为真
    void SetShouldClose(bool p_value) const;

    //如果窗口应该关闭则返回 true
    bool ShouldClose() const;

    //将窗口设置为全屏或窗口模式
    void SetFullscreen(bool p_value);

    //根据当前状态将窗口切换为全屏或窗口模式
    void ToggleFullscreen();

    //如果窗口是全屏则返回真
    bool IsFullscreen() const;

    //如果窗口被隐藏则返回真
    bool IsHidden() const;

    //如果窗口可见则返回真
    bool IsVisible() const;

    //如果窗口最大化则返回真
    bool IsMaximized() const;

    //如果窗口最小化则返回真
    bool IsMinimized() const;

    //如果窗口获得焦点则返回真
    bool IsFocused() const;

    //如果窗口可调整大小则返回 true
    bool IsResizable() const;

    //如果窗户被装饰则返回真
    bool IsDecorated() const;

    //定义窗口为当前上下文
    void MakeCurrentContext() const;

    //处理缓冲区与当前窗口的交换
    void SwapBuffers() const;

    //定义鼠标光标的模式
    void SetCursorMode(Cursor::ECursorMode p_cursorMode);

    //定义一个应用于当前光标的形状
    void SetCursorShape(Cursor::ECursorShape p_cursorShape);

    //移动光标到指定位置
    void SetCursorPosition(int16_t p_x, int16_t p_y);

    //定义窗口的标题
    void SetTitle(const std::string& p_title);

    //定义刷新率（使用 WindowSettings::DontCare 以使用最高可用刷新率）
    void SetRefreshRate(int32_t p_refreshRate);

    //返回窗口的标题
    std::string GetTitle() const;

    //返回当前窗口的大小
    std::pair<uint16_t, uint16_t> GetSize() const;

    //返回当前窗口的最小尺寸
    std::pair<int16_t, int16_t> GetMinimumSize() const;

    //返回当前窗口的最大尺寸
    std::pair<int16_t, int16_t> GetMaximumSize() const;

    //返回窗口的当前位置
    std::pair<int16_t, int16_t> GetPosition() const;

    //返回帧缓冲区大小（视口大小）
    std::pair<uint16_t, uint16_t> GetFramebufferSize() const;

    //返回当前光标模式
    Cursor::ECursorMode GetCursorMode() const;

    //返回当前光标形状
    Cursor::ECursorShape GetCursorShape() const;

    //返回当前刷新率（仅适用于全屏模式）。
    int32_t GetRefreshRate() const;

    //返回 GLFW 窗口
    GLFWwindow* GetGlfwWindow() const;

  private:
    void CreateGlfwWindow(const Settings::WindowSettings& p_windowSettings);

    void BindKeyCallback() const;
    void BindMouseCallback() const;
    void BindResizeCallback() const;
    void BindFramebufferResizeCallback() const;
    void BindCursorMoveCallback() const;
    void BindMoveCallback() const;
    void BindIconifyCallback() const;
    void BindFocusCallback() const;
    void BindCloseCallback() const;

    //事件监听器
    void OnResize(uint16_t p_width, uint16_t p_height);
    void OnMove(int16_t p_x, int16_t p_y);

    void UpdateSizeLimit() const;

  private:
    //回调使用此映射从“GLFWwindow”实例中查找“Window”实例
    static std::unordered_map<GLFWwindow*, Window*> __WINDOWS_MAP;

    const Context::Device& m_device;
    GLFWwindow* m_glfwWindow;

    std::string m_title;
    std::pair<uint16_t, uint16_t> m_size;
    std::pair<int16_t, int16_t> m_minimumSize;
    std::pair<int16_t, int16_t> m_maximumSize;
    std::pair<int16_t, int16_t> m_position;
    bool m_fullscreen;
    int32_t m_refreshRate;
    Cursor::ECursorMode m_cursorMode;
    Cursor::ECursorShape m_cursorShape;
  };
}

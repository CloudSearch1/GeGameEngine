#pragma once

#include <string>

namespace GeWindow::Settings
{
  //包含设备设置
	struct DeviceSettings
	{
    //指定是否创建调试 OpenGL 上下文，它可能具有额外的错误和性能问题报告功能。
    //如果请求 OpenGL ES，则忽略此提示
		bool debugProfile = false;

		bool forwardCompatibility = false;

    //指定创建的上下文必须与之兼容的客户端 API 主要版本。 最正确这些提示的行为取决于请求的客户端 API
		uint8_t contextMajorVersion = 3;

    //指定创建的上下文必须与之兼容的客户端 API 次要版本。 最正确这些提示的行为取决于请求的客户端 API
		uint8_t contextMinorVersion = 2;

    //定义要使用的样本数量（多重采样需要）
		uint8_t samples = 4;
	};
}

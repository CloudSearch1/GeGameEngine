#pragma once

#include <GeUI/Internal/WidgetContainer.h>

#include "GeCore/API/ISerializable.h"
#include "GeCore/Helpers/GUIDrawer.h"

namespace GeCore::API
{
  //IInspectorItem 是任何可在检查器上序列化和绘制的类的接口
	class IInspectorItem : public ISerializable
	{
	public:
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) = 0;
	};
}

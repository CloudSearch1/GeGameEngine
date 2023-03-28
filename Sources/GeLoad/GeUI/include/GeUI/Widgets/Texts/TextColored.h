#pragma once

#include "GeUI/Widgets/Texts/Text.h"
#include "GeUI/Types/Color.h"

namespace GeUI::Widgets::Texts
{
  //用于在面板上显示可以着色的文本的小部件
	class TextColored : public Text
	{
	public:
		TextColored(const std::string& p_content = "", const Types::Color& p_color = Types::Color(1.0f, 1.0f, 1.0f, 1.0f));
	public:
		Types::Color color;

	protected:
		virtual void _Draw_Impl() override;
	};
}

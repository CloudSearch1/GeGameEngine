#include "GeUtils/Utils/String.h"

bool GeUtils::Utils::String::Replace(std::string & p_target, const std::string & p_from, const std::string & p_to)
{
	size_t start_pos = p_target.find(p_from);

	if (start_pos != std::string::npos)
	{
		p_target.replace(start_pos, p_from.length(), p_to);
		return true;
	}

	return false;
}

void GeUtils::Utils::String::ReplaceAll(std::string& p_target, const std::string& p_from, const std::string& p_to)
{
	if (p_from.empty()) return;

	size_t start_pos = 0;
	while ((start_pos = p_target.find(p_from, start_pos)) != std::string::npos)
	{
		p_target.replace(start_pos, p_from.length(), p_to);
		start_pos += p_to.length();
	}
}

std::string GeUtils::Utils::String::GenerateUnique(const std::string& p_source, std::function<bool(std::string)> p_isAvailable)
{
    auto suffixlessSource = p_source;

    auto suffixOpeningParenthesisPos = std::string::npos;
    auto suffixClosingParenthesisPos = std::string::npos;

    //迭代到 `p_source` 时跟踪当前字符位置
    auto currentPos = decltype(std::string::npos){p_source.length() - 1};

    //这里我们搜索 `(` 和 `)` 位置。 （需要提取那些括号之间的数字）
    for (auto it = p_source.rbegin(); it < p_source.rend(); ++it, --currentPos)
    {
        const auto c = *it;

        if (suffixClosingParenthesisPos == std::string::npos && c == ')') suffixClosingParenthesisPos = currentPos;
        if (suffixClosingParenthesisPos != std::string::npos && c == '(') suffixOpeningParenthesisPos = currentPos;
    }

    // 我们需要在这里声明我们的 `counter` 来存储找到的括号之间的数字 OR 1（在没有找到括号，AKA，后缀的情况下）
    auto counter = uint32_t{ 1 };

    // 如果找到两个括号 AND 右括号是最后一个字符 AND 左括号前有一个空格
    if (suffixOpeningParenthesisPos != std::string::npos && suffixClosingParenthesisPos == p_source.length() - 1 && suffixOpeningParenthesisPos > 0 && p_source[suffixOpeningParenthesisPos - 1] == ' ')
    {
        // 提取括号之间的字符串
        const auto between = p_source.substr(suffixOpeningParenthesisPos + 1, suffixClosingParenthesisPos - suffixOpeningParenthesisPos - 1);

        // 如果 `between` 字符串由数字组成（又名，`between` 是一个数字）
        if (!between.empty() && std::find_if(between.begin(), between.end(), [](unsigned char c) { return !std::isdigit(c); }) == between.end())
        {
            counter = static_cast<uint32_t>(std::atoi(between.c_str()));
            suffixlessSource = p_source.substr(0, suffixOpeningParenthesisPos - 1);
        }
    }

    auto result = suffixlessSource;

    // 虽然 `result` 不可用，但我们会不断生成新字符串
    while (!p_isAvailable(result))
    {
        // 新字符串由 `suffixlessSource` 组成（例如：没有后缀的“Foo (1)”是“Foo”）
        result = suffixlessSource + " (" + std::to_string(counter++) + ")";
    }

    return result;
}

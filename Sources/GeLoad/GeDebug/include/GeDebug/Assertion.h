#pragma once

#include <string>


#define GEASSERT(condition, message) GeDebug::Assertion::Assert(condition, message)

namespace GeDebug
{
	class Assertion
	{
	public:

		Assertion() = delete;

    static void Assert(bool p_condition, const std::string& p_message = "");
	};
}

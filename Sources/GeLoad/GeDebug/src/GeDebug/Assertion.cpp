#include "GeDebug/Assertion.h"

#include <assert.h>

void GeDebug::Assertion::Assert(bool p_condition, const std::string& p_message)
{
	assert(p_condition && p_message.c_str());
}

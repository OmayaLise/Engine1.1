#pragma once

#define DEBUG

#include "Log.hpp"

namespace Core::Debug
{
#ifdef DEBUG
	#define Assertion(p_expression, p_log) if (!(p_expression)) { DEBUG_LOG(p_log); __debugbreak();}
#else
	#define Assertion(p_expression, p_log) if (!(p_expression)) { DEBUG_LOG(p_log); abort();}
#endif // DEBUG
}
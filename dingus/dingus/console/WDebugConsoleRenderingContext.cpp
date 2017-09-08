#include "dingus/console/WDebugConsoleRenderingContext.hpp"

using namespace dingus;

void CWDebugConsoleRenderingContext::write(const std::string& message)
{
	OutputDebugString(message.c_str());
}

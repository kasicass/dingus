#include "dingus/console/W32StdConsoleRenderingContext.hpp"

using namespace dingus;

CW32StdConsoleRenderingContext::CW32StdConsoleRenderingContext()
{
	AllocConsole();
	mConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	assert(mConsoleHandle);
}

CW32StdConsoleRenderingContext::~CW32StdConsoleRenderingContext()
{
	FreeConsole();
}

void CW32StdConsoleRenderingContext::write(const std::string& message)
{
	DWORD charsWritten;
	WriteConsole(mConsoleHandle, message.c_str(), (DWORD)message.length(), &charsWritten, NULL);
}

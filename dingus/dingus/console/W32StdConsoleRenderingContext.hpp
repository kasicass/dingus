#pragma once

#include "dingus/console/Console.hpp"

namespace dingus {

class CW32StdConsoleRenderingContext : public IConsoleRenderingContext
{
public:
	CW32StdConsoleRenderingContext();
	virtual ~CW32StdConsoleRenderingContext();

	void write(const std::string& message);

private:
	HANDLE mConsoleHandle;
};

}

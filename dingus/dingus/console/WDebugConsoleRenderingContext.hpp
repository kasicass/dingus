#pragma once

#include "dingus/console/Console.hpp"

namespace dingus {

class CWDebugConsoleRenderingContext : public IConsoleRenderingContext
{
public:
	CWDebugConsoleRenderingContext() {}
	virtual ~CWDebugConsoleRenderingContext() {}

	void write(const std::string& message);
};

}

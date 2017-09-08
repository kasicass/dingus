#pragma once

#include "dingus/console/Console.hpp"
#include <fstream>

namespace dingus {

class CFileConsoleRenderingContext : public IConsoleRenderingContext
{
public:
	CFileConsoleRenderingContext(const std::string& fileName);
	virtual ~CFileConsoleRenderingContext();

	virtual void write(const std::string& message) override;

private:
	std::ofstream mFile;
};

}

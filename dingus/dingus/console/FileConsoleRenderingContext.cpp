#include "dingus/console/FileConsoleRenderingContext.hpp"

using namespace dingus;

CFileConsoleRenderingContext::CFileConsoleRenderingContext(const std::string& fileName) :
	mFile(fileName)
{
}

CFileConsoleRenderingContext::~CFileConsoleRenderingContext()
{
}

void CFileConsoleRenderingContext::write(const std::string& message)
{
	mFile << message;
	mFile.flush();
}

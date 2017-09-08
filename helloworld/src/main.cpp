#include "dingus/console/Console.hpp"
#include "dingus/console/FileConsoleRenderingContext.hpp"
#include "dingus/console/WDebugConsoleRenderingContext.hpp"

using namespace dingus;

int main()
{
	// CWDebugConsoleRenderingContext consoleCtx;
	CFileConsoleRenderingContext consoleCtx("dingus_log.txt");

	CConsole &console = CConsole::getInstance();
	console.setDefaultRenderingContext(consoleCtx);
	
	CConsole::CON_ERROR.setLoggingTime(true);
	CConsole::CON_ERROR << "HelloWorld" << endl;
}

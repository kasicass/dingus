#include "dingus/console/Console.hpp"
#include "dingus/console/FileConsoleRenderingContext.hpp"
#include "dingus/console/WDebugConsoleRenderingContext.hpp"

#include "dingus/kernel/D3DDeviceCaps.hpp"

#include "dingus/lua/LuaWrapper.hpp"

using namespace dingus;

int main()
{
	// CWDebugConsoleRenderingContext consoleCtx;
	CFileConsoleRenderingContext consoleCtx("dingus_log.txt");

	CConsole &console = CConsole::getInstance();
	console.setDefaultRenderingContext(consoleCtx);
	
	CConsole::CON_ERROR.setLoggingTime(true);
	CConsole::CON_ERROR << "HelloWorld" << endl;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D)
	{
		UINT adapter = 0;
		D3DDEVTYPE devType = D3DDEVTYPE_HAL;
		D3DCAPS9 caps9;
		if (SUCCEEDED(pD3D->GetDeviceCaps(adapter, devType, &caps9)))
		{
			CD3DDeviceCaps mycaps;
			mycaps.setData(*pD3D, adapter, devType, caps9);

			CConsole::CON_ERROR << "CpuMhz: " << mycaps.getCpuMhz() << endl;
			CConsole::CON_ERROR << "VideoMem: " << mycaps.getVideoMemoryMB() << "MB" << endl;
			CConsole::CON_ERROR << "hasShadowMaps: " << mycaps.hasShadowMaps() << endl;
			CConsole::CON_ERROR << "hasFloatTextures: " << mycaps.hasFloatTextures() << endl;
			CConsole::CON_ERROR << "MRTCount: " << mycaps.getMRTCount() << endl;
		}
	}
	pD3D->Release();

	CLuaWrapper lua("data/");
	lua.doFile("main.lua", true);
	
	CLuaValue v = lua.getGlobal("VarA");
	printf("VarA = %f\n", v.getNumber());

	v = lua.getGlobal("VarB");
	printf("VarB = %s\n", v.getString().c_str());
}

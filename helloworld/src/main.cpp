#include "dingus/console/Console.hpp"
#include "dingus/console/FileConsoleRenderingContext.hpp"
#include "dingus/console/WDebugConsoleRenderingContext.hpp"

#include "dingus/kernel/D3DDeviceCaps.hpp"

#include "dingus/lua/LuaWrapper.hpp"
#include "dingus/lua/LuaIterator.hpp"
#include "dingus/lua/LuaHelper.hpp"

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

	v = lua.getGlobal("VarC");
	CLuaArrayIterator arrayC(v);
	while (arrayC.hasNext())
	{
		CLuaValue elem = arrayC.next();
		if (elem.isNumber()) printf("VarC[%d] = %f\n", arrayC.getKey(), elem.getNumber());
		else if (elem.isString()) printf("VarC[%d] = %s\n", arrayC.getKey(), elem.getString().c_str());
	}

	v = lua.getGlobal("VarD");
	std::string name = CLuaHelper::getString(v, "name");
	double age = CLuaHelper::getNumber(v, "age");
	SVector3 vec = CLuaHelper::getVector3(v, "pos");
	SQuaternion quat = CLuaHelper::getQuaternion(v, "quat");
	SMatrix4x4 m;
	CLuaHelper::getMatrix3x3(v, "matrix", m);

	CConsole::CON_ERROR << endl;
	CConsole::CON_ERROR << "VarD" << endl;
	CConsole::CON_ERROR << "  name: " << name << endl;
	CConsole::CON_ERROR << "  age: " << age << endl;
	CConsole::CON_ERROR << "  pos: " << vec << endl;
	CConsole::CON_ERROR << "  quat: " << quat << endl;
	CConsole::CON_ERROR << "  m: " << m << endl;
}

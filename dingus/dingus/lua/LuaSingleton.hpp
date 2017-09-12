#pragma once

#include "dingus/lua/LuaWrapper.hpp"
#include "dingus/utils/Singleton.hpp"

namespace dingus {

class CLuaSingleton : public CLuaWrapper, public CSingleton<CLuaSingleton>
{
public:
	static void init(const std::string& predir)
	{
		CLuaSingleton *lua = new CLuaSingleton(predir);
		assert(lua);
		assignInstance(*lua);
	}

private:
	IMPLEMENT_SIMPLE_SINGLETON(CLuaSingleton);

	CLuaSingleton() : CLuaWrapper("data/") { ASSERT_FAIL_MSG("musst be init() first"); }
	CLuaSingleton(const std::string& predir) : CLuaWrapper(predir) { }
};

}

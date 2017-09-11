#pragma once

#include "lua/src/lua.hpp"
#include "dingus/GlobalSetting.hpp"
#include "dingus/lua/LuaValue.hpp"

namespace dingus {

class CLuaWrapper
{
public:
	CLuaWrapper(const std::string& basePath);
	~CLuaWrapper();

	CLuaValue getGlobal(const char* name);
	CLuaValue getGlobal(const std::string& name);
	void      clearGlobal(const char* name);
	void      clearGlobal(const std::string& name);

	int doFile(const char* fileName, bool addBasePath);
	int doString(const char* str);

	// discards last obtained value
	void discard() { lua_pop(mState, 1); }

	// Was last parse errorneous?
	bool isError() const { return mError != 0; }
	const char* getError() const;

	lua_State* getState() const { return mState; }

private:
	lua_State* mState;
	int mError;
	std::string mBasePath;
};

inline int CLuaWrapper::doFile(const char* fileName, bool addBasePath)
{
	assert(fileName != NULL);
	return luaL_dofile(mState, addBasePath ? ((mBasePath+fileName).c_str()) : fileName);
}

inline int CLuaWrapper::doString(const char* str)
{
	assert(str != NULL);
	return luaL_dostring(mState, str);
}

}

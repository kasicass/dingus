#include "dingus/lua/LuaWrapper.hpp"
#include "dingus/lua/LuaValue.hpp"

using namespace dingus;

CLuaWrapper::CLuaWrapper(const std::string& basePath) :
	mError(0),
	mState(NULL),
	mBasePath(basePath)
{
	mState = luaL_newstate();
	assert(mState);
}

CLuaWrapper::~CLuaWrapper()
{
	// TODO(kasicass): free mState
}

const char* CLuaWrapper::getError() const
{
	return strerror(mError);
}

CLuaValue CLuaWrapper::getGlobal(const char* name)
{
	lua_getglobal(mState, name);
	return CLuaValue(*this, lua_gettop(mState));
}

CLuaValue CLuaWrapper::getGlobal(const std::string& name)
{
	return getGlobal(name.c_str());
}

void CLuaWrapper::clearGlobal(const char* name)
{
	lua_pushnil(mState);
	lua_setglobal(mState, name);
}

void CLuaWrapper::clearGlobal(const std::string& name)
{
	clearGlobal(name.c_str());
}


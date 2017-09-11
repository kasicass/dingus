#include "dingus/lua/LuaValue.hpp"
#include "dingus/lua/LuaWrapper.hpp"

using namespace dingus;

bool CLuaValue::isInvalid() const
{
	return mLua == 0;
}

bool CLuaValue::isNil() const
{
	return lua_isnil(mLua->getState(), mIndex);
}

bool CLuaValue::isNumber() const
{
	return lua_isnumber(mLua->getState(), mIndex) ? true : false;
}

bool CLuaValue::isString() const
{
	return lua_isstring(mLua->getState(), mIndex) ? true : false;
}

bool CLuaValue::isTable() const
{
	return lua_istable(mLua->getState(), mIndex);
}

bool CLuaValue::isFunction() const
{
	return lua_isfunction(mLua->getState(), mIndex);
}

double CLuaValue::getNumber() const
{
	return lua_tonumber(mLua->getState(), mIndex);
}

std::string CLuaValue::getString() const
{
	size_t n;
	const char* s = lua_tolstring(mLua->getState(), mIndex, &n);
	if (s)
	{
		return std::string(s, n);
	}
	else
	{
		return "";
	}
}

CLuaValue CLuaValue::getElement(const std::string& key) const
{
	return getElement(key.c_str());
}

CLuaValue CLuaValue::getElement(const char* key) const
{
	lua_State* L = mLua->getState();
	lua_pushstring(L, key);
	lua_rawget(L, mIndex);
	return CLuaValue(*mLua, lua_gettop(L));
}

CLuaValue CLuaValue::getElement(double key) const
{
	lua_State* L = mLua->getState();
	lua_pushnumber(L, key);
	lua_rawget(L, mIndex);
	return CLuaValue(*mLua, lua_gettop(L));
}

void CLuaValue::discard()
{
	mLua->discard();
}

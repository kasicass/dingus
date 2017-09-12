#pragma once

#include "dingus/GlobalSetting.hpp"
#include "dingus/lua/LuaValue.hpp"

namespace dingus {

class CLuaArrayIterator : public boost::noncopyable
{
public:
	CLuaArrayIterator(CLuaValue& val);
	~CLuaArrayIterator();

	bool hasNext() const;

	CLuaValue& next();

	int getKey() const { return mIndex-1; }

private:
	CLuaWrapper* mLua;
	CLuaValue*   mValue;
	CLuaValue    mFetchedElem;
	int          mIndex;
};

}

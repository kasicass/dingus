#include "dingus/lua/LuaIterator.hpp"
#include "dingus/lua/LuaWrapper.hpp"

using namespace dingus;

CLuaArrayIterator::CLuaArrayIterator(CLuaValue& val) :
	mLua(&val.getLua()),
	mValue(&val),
	mFetchedElem(val.isTable() ? val.getElement(1) : CLuaValue()),
	mIndex(1)
{
}

CLuaArrayIterator::~CLuaArrayIterator()
{
	if (mValue->isTable())
		mLua->discard();
}

bool CLuaArrayIterator::hasNext() const
{
	if (!mValue->isTable())
		return false;

	bool ok = !mValue->getElement(mIndex).isNil();
	mLua->discard();
	return ok;
}

CLuaValue& CLuaArrayIterator::next()
{
	assert(hasNext());

	if (mIndex == 1)
	{
		++mIndex;
	}
	else
	{
		mLua->discard();
		mFetchedElem = mValue->getElement(mIndex);
		++mIndex;
	}

	return mFetchedElem;
}

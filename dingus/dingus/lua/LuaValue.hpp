#pragma once

#include <string>

namespace dingus {

class CLuaWrapper;

class CLuaValue
{
public:
	CLuaValue() : mLua(0), mIndex(0) {}

	bool isInvalid() const;
	bool isNil() const;
	bool isNumber() const;
	bool isString() const;
	bool isTable() const;
	bool isFunction() const;

	double      getNumber() const;
	std::string getString() const;
	CLuaValue   getElement(const std::string& key) const;
	CLuaValue   getElement(const char* key) const;
	CLuaValue   getElement(double key) const;

	const CLuaWrapper& getLua() const { return *mLua; }
	CLuaWrapper& getLua() { return *mLua; }

	void discard();

protected:
	CLuaValue(CLuaWrapper& lua, int index) : mLua(&lua), mIndex(index) {}

private:
	friend class CLuaWrapper;

private:
	CLuaWrapper* mLua;
	int          mIndex;
};

}

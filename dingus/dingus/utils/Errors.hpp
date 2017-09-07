#pragma once

#include <string>
#include <stdexcept>

namespace dingus {

#define THROW_ERROR(msg) { \
	assert(false); \
	throw EBaseError(msg, __FILE__, __LINE__); \
	}

#define THROW_DXERROR(hr, msg) { \
	assert(false); \
	char buf[100]; \
	sprintf(buf, "%X ", hr); \
	throw EBaseError(std::string(buf) + msg, __FILE__, __LINE__); \
	}

class EBaseError : public std::runtime_error
{
public:
	EBaseError(const std::string &msg, const char* fileName, int lineNumber);

	virtual const char* what() const override { return mWhereMsg.c_str(); }

	const char* getFileName() const { return mFileName; }
	int getLineNumber() const { return mLineNumber; }

protected:
	std::string mWhereMsg;
	const char* mFileName;
	int         mLineNumber;
};

}

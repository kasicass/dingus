#pragma once

namespace dingus {

class CConsoleChannel;

class IResourceBundle
{
public:
	static CConsoleChannel& CONSOLE;

public:
	virtual ~IResourceBundle() {}
};

}

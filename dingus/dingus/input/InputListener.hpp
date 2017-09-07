#pragma once

namespace dingus
{

class CInputEvent;

class IInputListener
{
public:
	virtual ~IInputListener() {}

	virtual void onInputEvent(const CInputEvent &e) = 0;
	virtual void onInputStage() = 0;
};

}
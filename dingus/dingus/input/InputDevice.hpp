#pragma once

#include "dingus/input/InputEvent.hpp"

namespace dingus {

class IInputDevice
{
public:
	virtual ~IInputDevice() {}

	virtual CInputEvents poll() = 0;
};

}

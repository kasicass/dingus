#pragma once

#include "dingus/utils/Notifier.hpp"
#include "dingus/input/InputListener.hpp"
#include "dingus/input/InputEvent.hpp"

namespace dingus {

class IInputDevice;

class CInputContext : public CNotifier<IInputListener>
{
public:
	typedef fastvector<IInputDevice*> TDeviceContainer;

public:
	void addDevice(IInputDevice &device) { devices_.push_back(&device); }
	void removeDevice(IInputDevice &device) { devices_.remove(&device); }
	const TDeviceContainer& getDevices() const { return devices_; }
	TDeviceContainer& getDevices() { return devices_; }

	void perform();

private:
	TDeviceContainer devices_;
};

}

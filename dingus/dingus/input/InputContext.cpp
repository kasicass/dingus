#include "dingus/input/InputContext.hpp"
#include "dingus/input/InputDevice.hpp"

using namespace dingus;

void CInputContext::perform()
{
	// poll devices, notify listeners
	TDeviceContainer::iterator dit, ditEnd = devices_.end();
	for (dit = devices_.begin(); dit != ditEnd; ++dit)
	{
		IInputDevice *device = *dit;
		assert(device);

		CInputEvents polled(device->poll());
		CInputEvents::TEventsVector::const_iterator it, itEnd = polled.getEvents().end();
		for (it = polled.getEvents().begin(); it != itEnd; ++it)
		{
			const CInputEvent &e = **it;
			assert(&e);

			TListenerVector::iterator lit, litEnd = getListeners().end();
			for (lit = getListeners().begin(); lit != litEnd; ++lit)
			{
				(*lit)->onInputEvent(e);
			}
		}
	}

	// end-stage listeners notify
	TListenerVector::iterator lit, litEnd = getListeners().end();
	for (lit = getListeners().begin(); lit != litEnd; ++lit)
	{
		(*lit)->onInputStage();
	}
}

#pragma once

#include "dingus/utils/Notifier.hpp"

namespace dingus {

// Reloadable resource (usually bundle).
//
// Is able to reload all the resources it contains. The application won't
// notice this, because it's dealing with proxies anyway. Reloading should
// preserve the resource proxy objects, only change the objects they refer to.
class IReloadableBundle
{
public:
	virtual ~IReloadableBundle() {}

	virtual void reload() = 0;
};

// Manager for reloadable bundles.
class CReloadableBundleManager : public IReloadableBundle, public CNotifier<IReloadableBundle>
{
public:
	virtual void reload() override
	{
		auto listeners = getListeners();
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->reload();
		}
	}
};

}

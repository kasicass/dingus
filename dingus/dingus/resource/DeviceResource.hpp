#pragma once

// #include "dingus/resource/ReloadableBundle.hpp"
#include "dingus/utils/Singleton.hpp"
#include "dingus/utils/Notifier.hpp"

namespace dingus {

// D3D device dependant resource
class IDeviceResource
{
public:
	virtual ~IDeviceResource() {}

	virtual void createResource() = 0;
	virtual void activateResource() = 0;
	virtual void passivateResource() = 0;
	virtual void deleteResource() = 0;
};

#if 0
class IDeviceReloadableBundle : public IDeviceResource, public IReloadableBundle
{
public:
	virtual void reload() override
	{
		passivateResource();
		deleteResource();
		createResource();
		activateResource();
	}
};
#endif



class CDeviceResourceManager : public IDeviceResource, public CNotifier<IDeviceResource>, public CSingleton<CDeviceResourceManager>
{
public:
	virtual void passivateResource() override
	{
		auto listeners = getListeners();
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->passivateResource();
		}
	}

	virtual void deleteResource() override
	{
		auto listeners = getListeners();
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->deleteResource();
		}
	}

	virtual void createResource() override
	{
		auto listeners = getListeners();
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->createResource();
		}
	}

	virtual void activateResource() override
	{
		auto listeners = getListeners();
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->activateResource();
		}
	}

private:
	IMPLEMENT_SIMPLE_SINGLETON(CDeviceResourceManager);
	CDeviceResourceManager() {}
	virtual ~CDeviceResourceManager() {}
};

}

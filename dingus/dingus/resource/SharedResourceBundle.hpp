#pragma once

#include "dingus/GlobalSetting.hpp"
#include "dingus/resource/ResourceBundle.hpp"
#include "dingus/resource/ResourceId.hpp"

namespace dingus {

template <typename T, typename RESDATA>
class CSharedResourceBundle : public IResourceBundle
{
private:
	typedef std::map<CResourceId, std::pair<RESDATA, T*>> TResourceMap;

public:
	CSharedResourceBundle() {}
	virtual ~CSharedResourceBundle() {}

	T* getResoruceById(const CResourceId& id)
	{
		T* resource = findResource(id);
		assert(resource);
		return resource;
	}

	// NOTE: deletes the resource, so make sure no one references it!
	void unregisterResource(const CResourceId& id)
	{
		T* resource = findResource(id);
		if (resource)
		{
			deleteResource(*resource);
			mResourceMap.erase(id);
		}
	}

	void clear()
	{
		for (TResourceMap::iterator it = mResourceMap.begin(); it != mResourceMap.end(); )
		{
			assert(it->second.second);
			deleteResource(*it->second.second);
			it = mResourceMap.erase(it);
		}
	}

protected:
	void registerResource(const CResourceId& id, T& resource, RESDATA data)
	{
		std::pair<RESDATA, T*> pr(data, &resource);
		mResourceMap.insert(std::make_pair(id, pr));
	}

	T* findResource(const CResourceId& id)
	{
		TResourceMap::const_iterator it = mResourceMap.find(id);
		return (it != mResourceMap.end()) ? it->second.second : NULL;
	}

	virtual void deleteResource(T& resource) = 0;

protected:
	TResourceMap mResourceMap;
};

}

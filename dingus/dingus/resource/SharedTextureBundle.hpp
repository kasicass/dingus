#pragma once

#include "dingus/resource/SharedResourceBundle.hpp"
#include "dingus/resource/TextureCreator.hpp"
#include "dingus/resource/DeviceResource.hpp"
#include "dingus/kernel/Proxies.hpp"
#include "dingus/utils/Singleton.hpp"

namespace dingus {

class CSharedTextureBundle : public CSharedResourceBundle<CD3DTexture, ITextureCreator::TShreadPtr>,
                             public CSingleton<CSharedTextureBundle>,
							 public IDeviceResource
{
public:
	void registerTexture(const CResourceId& id, ITextureCreator& creator);

	virtual void createResource() override;
	virtual void activateResource() override;
	virtual void passivateResource() override;
	virtual void deleteResource() override;

protected:
	virtual void deleteResource(CD3DTexture& resource)
	{
		if (resource.getObject())
			resource.getObject()->Release();
		delete &resource;
	}

private:
	IMPLEMENT_SIMPLE_SINGLETON(CSharedTextureBundle);
	CSharedTextureBundle() {}
	virtual ~CSharedTextureBundle() { clear(); }
};

}

#define RGET_S_TEX(rid) dingus::CSharedTextureBundle::getInstance().getResoruceById(rid)


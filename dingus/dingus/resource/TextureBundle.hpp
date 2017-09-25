#pragma once

#include "dingus/resource/StorageResourceBundle.hpp"
#include "dingus/resource/DeviceResource.hpp"
#include "dingus/kernel/Proxies.hpp"
#include "dingus/utils/Singleton.hpp"

namespace dingus {

class CTextureBundle : public CStorageResourceBundle<CD3DTexture>,
					   public CSingleton<CTextureBundle>,
					   public IDeviceResource
{
public:
	// IDeviceResource
	virtual void createResource() override;
	virtual void activateResource() override;
	virtual void passivateResource() override;
	virtual void deleteResource() override;

protected:
	// CStorageResourceBundle
	virtual CD3DTexture* loadResourceById(const CResourceId& id, const CResourceId& fullName) override;
	virtual void deleteResource(CD3DTexture& resource) override;

private:
	IMPLEMENT_SIMPLE_SINGLETON(CTextureBundle);
	CTextureBundle();
	virtual ~CTextureBundle();

	IDirect3DTexture9* loadTexture(const CResourceId& id, const CResourceId& fullName) const;
};

#define RGET_TEX(rid) dingus::CTextureBundle::getInstance().getResourceById(rid)

}


#pragma once

#include "dingus/resource/StorageResourceBundle.hpp"
#include "dingus/resource/DeviceResource.hpp"
#include "dingus/kernel/Proxies.hpp"
#include "dingus/utils/Singleton.hpp"

namespace dingus {

// D3DX Effects bundle
//
// Enables conditional compilation of effects via macros (name-value pairs),
// see setMacro() and removeMacro()
class CEffectBundle : public CStorageResourceBundle<CD3DXEffect>,
                      public CSingleton<CEffectBundle>,
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
	virtual CD3DXEffect* loadResourceById(const CResourceId& id, const CResourceId& fullName) override;
	virtual void deleteResource(CD3DXEffect& resource) override;

public:
	void setStatesConfig(const char* filename);

	bool isOptimizingShaders() const { return mOptimizeShaders; }
	void setOptimizeShaders(bool opt) { mOptimizeShaders = opt; }
	bool isUsingStateManager() const { return mUseStateManager; }
	void setUsingStateManager(bool stmgr) { mUseStateManager = stmgr; }

	const std::string& getLastErrors() const { return mLastErrors; }

	// Adds macro (or replaces same-named one).
	// After changing a bunch of macros, call reload() to actually reload effects.
	// NOTE: name/value strings are not copied, so look at their lifetime!
	void setMacro(const char* name, const char* value);

	// Removes macros.
	// After changing a bunch of macros, call reload() to actually reload effects.
	void removeMacro(const char* name);

private:
	IMPLEMENT_SIMPLE_SINGLETON(CEffectBundle);
	CEffectBundle();
	virtual ~CEffectBundle();

	// return index into macro array, or -1 if not found.
	int findMacro(const char* name) const;

private:
	ID3DXEffectPool* mSharedPool;

	bool mUseStateManager;
	bool mOptimizeShaders;
	mutable std::string mLastErrors;

	typedef std::vector<D3DXMACRO> TMacroVector;
	TMacroVector mMacros;
};

}

#define RGET_FX(rid) dingus::CEffectBundle::getInstance().getResourceById(rid)

#include "dingus/resource/EffectBundle.hpp"
#include "dingus/kernel/EffectLoader.hpp"
#include "dingus/kernel/D3DDevice.hpp"
#include "dingus/utils/Errors.hpp"

using namespace dingus;

CEffectBundle::CEffectBundle() :
	mSharedPool(0),
	mOptimizeShaders(true),
	mUseStateManager(true),
	mLastErrors("")
{
	addExtension(".fx");

	mMacros.reserve(16);

	// last macro must be NULL
	mMacros.push_back(D3DXMACRO());
	mMacros.back().Name = mMacros.back().Definition = NULL;
}

CEffectBundle::~CEffectBundle()
{
	clear();
	fxloader::shutdown();
}

void CEffectBundle::setStatesConfig(const char* filename)
{
	bool ok = fxloader::initialize(filename);
	if (!ok)
	{
		CConsole::CON_ERROR << "EffectBundle: failed to load states configuration from " << filename << endl;
	}
}

int CEffectBundle::findMacro(const char* name) const
{
	int n = (int)mMacros.size() - 1;  // last one is NULL anyway
	for (int i = 0; i < n; ++i)
	{
		if (strcmp(name, mMacros[i].Name) == 0)
			return i;
	}
	return -1; // not found
}

void CEffectBundle::setMacro(const char* name, const char* value)
{
	int idx = findMacro(name);
	if (idx >= 0)
	{
		// have existing one, replace
		mMacros[idx].Definition = value;
	}
	else
	{
		// replace last (which was NULL)
		size_t lastIdx = mMacros.size() - 1;
		mMacros[lastIdx].Name = name;
		mMacros[lastIdx].Definition = value;

		// last macro must be NULL
		mMacros.push_back(D3DXMACRO());
		mMacros.back().Name = mMacros.back().Definition = NULL;
	}
}

void CEffectBundle::removeMacro(const char* name)
{
	int idx = findMacro(name);
	if (idx >= 0)
	{
		size_t preLastIdx = mMacros.size() - 2;
		mMacros[idx] = mMacros[preLastIdx];
		mMacros[preLastIdx].Name = mMacros[preLastIdx].Definition = NULL;
		mMacros.pop_back();
	}
}

CD3DXEffect* CEffectBundle::loadResourceById(const CResourceId& id, const CResourceId& fullName)
{
	CD3DXEffect* fx = new CD3DXEffect(NULL);
	bool ok = fxloader::load(id.getUniqueName(), fullName.getUniqueName(), NULL,
		*fx, mLastErrors, mSharedPool,
		mUseStateManager ? (&CD3DDevice::getInstance().getStateManager()) : NULL,
		&mMacros[0], mMacros.size(), mOptimizeShaders, CONSOLE);
	if (!ok)
	{
		delete fx;
		return NULL;
	}
	return fx;
}

void CEffectBundle::createResource()
{
	// create pool
	assert(!mSharedPool);
	D3DXCreateEffectPool(&mSharedPool);
	assert(mSharedPool);

	// reload all objects
	TResourceMap::iterator it;
	for (it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
	{
		CD3DXEffect& res = *it->second;
		assert(res.isNull());
		CD3DXEffect* n = tryLoadResourceById(it->first);
		assert(n);
		res.setObject( n->getObject() );
		delete n;
		assert(!res.isNull());
	}
}

void CEffectBundle::activateResource()
{
	// call reset on effects
	TResourceMap::iterator it;
	for (it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
	{
		CD3DXEffect& res = *it->second;
		assert(!res.isNull());
		res.getObject()->OnResetDevice();
	}
}

void CEffectBundle::passivateResource()
{
	// call lost on effects
	TResourceMap::iterator it;
	for (it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
	{
		CD3DXEffect& res = *it->second;
		assert(!res.isNull());
		res.getObject()->OnResetDevice();
	}
}

void CEffectBundle::deleteResource()
{
	// unload all objects
	TResourceMap::iterator it;
	for (it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
	{
		CD3DXEffect& res = *it->second;
		assert(!res.isNull());
		res.getObject()->Release();
		res.setObject(NULL);
	}

	// release pool
	assert(mSharedPool);
	mSharedPool->Release();
	mSharedPool = NULL;
}


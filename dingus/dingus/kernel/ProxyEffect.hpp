#pragma once

#include "dingus/kernel/Proxies.hpp"

#define DINGUS_FX_RESTORE_PASS "PLast"

namespace dingus {

// Proxy for ID3DXEffect with some addons.
//
// Additionally has some indicators:
//  - whether this effect requires strict back-to-front sorting.
//  - required vertex shader version (0, 1.1, 2.0 or 3.0 currently)
// The indicators are read from effect technique annotations.
class CD3DXEffect : public CBaseProxyClass
{
	CD3DXEffect(ID3DXEffect *object = 0);

	int beginFx();            // return Number of passes;
	void endFx();
	void beginPass(int p);
	void endPass();
	void commitParams();      // commits parameters that are set after begin

	ID3DXEffect* getObject() const { return reinterpret_cast<ID3DXEffect*>(getPtr()); }
	void setObject(ID3DXEffect *object);

	bool isBackToFrontSorted() const { return mBackToFrontSorted; }
	bool isSoftwareVertexProcessed() const { return mSoftwareVertexProcessed; }
	bool hasRestoringPass() const { return mHasRestoringPass; }

	// For sorting, computed from other params in ascending order.
	// Orders by back-to-front (non-sorted first, then sorted), then
	// by vshader version in ascending order.
	int getSortValue() const { return mSortValue; }

private:
	void init();
	bool tryInit();
	bool isValidTechnique(D3DXHANDLE tech);

private:
	int mPassCount; // count or count-1, depending on presence of restoring pass
	int mSortValue; // value computed from other params, for sorting
	bool mBackToFrontSorted;
	bool mSoftwareVertexProcessed;
	bool mHasRestoringPass;
};

}

#pragma once

namespace dingus {

class CRenderStats
{
public:
	struct SStateStats {
		int transforms;
		int lighting;      // materials + light + lightenable
		int renderStates;
		int textures;
		int textureStages;
		int samplers;
		int vsh;
		int psh;
		int vshConst;
		int pshConst;
		int declarations;  // declaration / fvf
		int vbuffer;
		int ibuffer;
		int renderTarget;
		int zStencil;
	};

public:
	CRenderStats() { reset(); }

	int getDrawCalls() const { return mDrawCalls; }
	int getVerticesRendered() const { return mVerticesRendered; }
	int getPrimsRendered() const { return mPrimsRendered; }
	int getEffectChanges() const { return mEffectChanges; }

	void incDrawCalls() { ++mDrawCalls; }
	void incVerticesRendered(int by) { mVerticesRendered += by; }
	void incPrimsRendered(int by) { mPrimsRendered += by; }
	void incEffectChanges() { ++mEffectChanges; }

	void setFPS(float fps) { mFPS = fps; }
	float getFPS() const { return mFPS; }

	void reset();

public:
	SStateStats changes;   // state changes actually made
	SStateStats filtered;  // state changes filtered

private:
	int mDrawCalls;
	int mEffectChanges;
	int mVerticesRendered;
	int mPrimsRendered;
	float mFPS;
};

}

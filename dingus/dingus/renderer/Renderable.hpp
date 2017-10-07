#pragma once

#include "dingus/utils/Notifier.hpp"
#include "dingus/renderer/EffectParams.hpp"
#include "dingus/renderer/RenderContext.hpp"

namespace dingus {

class CRenderable;

class IRenderListener
{
public:
	virtual ~IRenderListener() = 0 {}

	virtual void beforeRender(CRenderable& r, CRenderContext& ctx) = 0;
	virtual void afterRender(CRenderable& r, CRenderContext& ctx) = 0;
};

// Base renderable class.
//
// Contains parameters for the rendering (effect params, priority and origin),
// virtual method render() and before/after rendering listeners. Note that
// render() may be called multiple times if the effect is multi-pass.
//
// The renderable should generally only render it's geometry. The render states
class CRenderable : public CNotifier<IRenderListener>
{
public:
	CRenderable(const SVector3* origin = 0, int priority = 0) : mOrigin(origin), mPriority(priority) {}
	virtual ~CRenderable() {}

	const CEffectParams& getParams() const { return mParams; }
	CEffectParams& getParams() { return mParams; }

	int getPriority() const { return mPriority; }
	void setPriority(int priority) { mPriority = priority; }

	const SVector3* getOrigin() const { return mOrigin; }
	void setOrigin(const SVector3* o) { mOrigin = o; }
	bool isOrigin() const { return mOrigin != NULL; }

	void beforeRender(CRenderContext& ctx);
	void afterRender(CRenderContext& ctx);

	// Called for each rendering pass. Here one should render it's geometry.
	// Note that this may be called multiple times for a multi-pass effect.
	virtual void render(const CRenderContext& ctx) {}

	// Return used VB ("main" one, eg. stream zero) - for sorting by VB
	virtual const CD3DVertexBuffer* getUsedVB() const = 0;
	// Return used IB - for sorting by IB
	virtual const CD3DIndexBuffer* getUsedIB() const = 0;

private:
	CEffectParams   mParams;     // Effect and it's params
	int             mPriority;   // Render priority. Renderables with lesser priority will be rendered sooner.
	const SVector3* mOrigin;     // Origin of the renderable object, used for sorting. May be null.
};

}

#pragma once

#include "dingus/renderer/Renderable.hpp"
#include "dingus/kernel/Proxies.hpp"
#include "dingus/utils/MemoryPool.hpp"

namespace dingus {

class CRenderContext;

namespace renderquad {
	struct SCoordRect
	{
		SCoordRect() {}
		SCoordRect(float _u1, float _v1, float _u2, float _v2) :
			u1(_u1), v1(_v1), u2(_u2), v2(_v2) {}

		float u1, v1;
		float u2, v2;
	};

	// Calculate texture coordinates to use when rendering into
	// destination texture, given the source and destination rectangles.
	void calcCoordRect(
		CD3DTexture& srcTex, const RECT* srcRect,
		CD3DTexture& dstTex, const RECT* dstRect,
		SCoordRect& coords);
}

// --------------------------------------------------------------------------

// Renders correctly aligned fullscreen quad.
class CRenderableQuad : public CRenderable
{
public:
	CRenderableQuad(const renderquad::SCoordRect& uvRect, int priority = 0);
	
	void setUVRect(const renderquad::SCoordRect& uvRect) { mUVRect = uvRect; }

	virtual void render(const CRenderContext& ctx);
	virtual const CD3DIndexBuffer*  getUsedIB() const { return NULL; }
	virtual const CD3DVertexBuffer* getUsedVB() const { return NULL; }

private:
	DECLARE_POOLED_ALLOC(dingus::CRenderableQuad);

private:
	renderquad::SCoordRect mUVRect;
};

}
#include "dingus/renderer/Renderable.hpp"

using namespace dingus;

void CRenderable::beforeRender(CRenderContext& ctx)
{
	auto it = getListeners().begin();
	auto itEnd = getListeners().end();
	while (it != itEnd)
	{
		assert(*it);
		(*it)->beforeRender(*this, ctx);
	}
}

void CRenderable::afterRender(CRenderContext& ctx)
{
	auto it = getListeners().begin();
	auto itEnd = getListeners().end();
	while (it != itEnd)
	{
		assert(*it);
		(*it)->afterRender(*this, ctx);
	}
}

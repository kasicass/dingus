#include "dingus/renderer/EffectParamsNotifier.hpp"

using namespace dingus;

void CEffectParamsNotifier::notify()
{
	auto itEnd = getListeners().end();
	for (auto it = getListeners().begin(); it != itEnd; ++it)
	{
		CEffectParams* ep = *it;
		assert(ep);

		ep->setEffect(*ep->getEffect(), true);
	}
}

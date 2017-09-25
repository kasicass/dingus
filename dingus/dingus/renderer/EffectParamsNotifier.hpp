#pragma once

#include "dingus/renderer/EffectParams.hpp"
#include "dingus/utils/Notifier.hpp"
#include "dingus/utils/Singleton.hpp"

namespace dingus {

// Notifies effect params on effect object change.
//
// Effect params objects register to the notifier, and unregister when
// destroyed. You need to notify them when the effect objects change (eg. on
// effects reload, on device change etc.).
class CEffectParamsNotifier : public CNotifier<CEffectParams>,
                              public CSingleton<CEffectParamsNotifier>
{
public:
	void notify();

private:
	IMPLEMENT_SIMPLE_SINGLETON(CEffectParamsNotifier);
};

}

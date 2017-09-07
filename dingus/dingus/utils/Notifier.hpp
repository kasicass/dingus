#pragma once

#include "dingus/GlobalSetting.hpp"

namespace dingus
{

// Notifier class. Provides listener registry, listener notification
// is left to subclasses.
//
// Note that it doesn't have virtual functionality at all
// (eg. no virtual destructor).
template <typename T>
class CNotifier
{
public:
	typedef fastvector<T*> TListenerVector;

public:
	void addListener(T& listener) { listeners_.push_back(&listener); }
	void removeListener(T& listener) { listeners_.remove(&listener); }
	void clearListeners() { listeners_.clear(); }

	const TListenerVector& getListeners() const { return listeners_; }
	TListenerVector& getListeners() { return listeners_; }

private:
	TListenerVector listeners_;
};

}

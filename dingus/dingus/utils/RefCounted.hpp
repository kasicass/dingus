#pragma once

#define DingusSmartPtr boost::intrusive_ptr

namespace dingus
{

class CRefCounted : public boost::noncopyable
{
public:
	CRefCounted() : refCount_(0) {}
	virtual ~CRefCounted() {}

	int decRef();
	int incRef();
	int getRefCount() const { return refCount_; }

private:
	int refCount_;
};

inline int CRefCounted::incRef()
{
	return ++refCount_;
}

inline int CRefCounted::decRef()
{
	assert(refCount_ > 0);
	int refs = --refCount_;
	if (!refCount_)
		delete this;
	return refs;
}

}

// for boost::intrusive_ptr
namespace boost
{
	inline void intrusive_ptr_add_ref(dingus::CRefCounted *p) { p->incRef(); }
	inline void intrusive_ptr_release(dingus::CRefCounted *p) { p->decRef(); }
}

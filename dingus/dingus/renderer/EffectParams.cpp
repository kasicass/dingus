#include "dingus/renderer/EffectParams.hpp"
#include "dingus/renderer/EffectParamsNotifier.hpp"

using namespace dingus;

CEffectParams::CEffectParams() : mEffect(0)
{
	CEffectParamsNotifier::getInstance().addListener(*this);
}

CEffectParams::~CEffectParams()
{
	CEffectParamsNotifier::getInstance().removeListener(*this);
}

CEffectParams::CEffectParams(const CEffectParams& rhs) :
	mEffect(rhs.mEffect),
	mParams1(rhs.mParams1),
	mParams3(rhs.mParams3),
	mParams4(rhs.mParams4),
	mParams16(rhs.mParams16),
	mParamsPtr(rhs.mParamsPtr),
	mParamsProxy(rhs.mParamsProxy)
{
	CEffectParamsNotifier::getInstance().addListener(*this);
}

const CEffectParams& CEffectParams::operator=(const CEffectParams& rhs)
{
	mEffect      = rhs.mEffect;
	mParams1     = rhs.mParams1;
	mParams3     = rhs.mParams3;
	mParams4     = rhs.mParams4;
	mParams16    = rhs.mParams16;
	mParamsPtr   = rhs.mParamsPtr;
	mParamsProxy = rhs.mParamsProxy;
	return *this;
}

void CEffectParams::initHandle(SParamHandle& par) const
{
	if (!mEffect)
		return;
	par.handle = mEffect->getObject()->GetParameterByName(NULL, par.name.c_str());
}

void CEffectParams::addInt(TParamName name, int i)
{
	mParams1.push_back(SParam1());
	SParam1& par = mParams1.back();
	par.name = name;
	initHandle(par);
	par.valI = i;
}

void CEffectParams::addVector3(TParamName name, const SVector3& v)
{
	mParams3.push_back(SParam3());
	SParam3& par = mParams3.back();
	par.name = name;
	initHandle(par);
	par.valV = v;
}

void CEffectParams::addVector4(TParamName name, const SVector4& v)
{
	mParams4.push_back(SParam4());
	SParam4& par = mParams4.back();
	par.name = name;
	initHandle(par);
	par.valV = v;
}

void CEffectParams::addMatrix4x4(TParamName name, const SMatrix4x4& v)
{
	mParams16.push_back(SParam16());
	SParam16& par = mParams16.back();
	par.name = name;
	initHandle(par);
	par.valM = v;
}

void CEffectParams::addPtr(TParamName name, int size, const void* ptr)
{
	mParamsPtr.push_back(SParamPtr());
	SParamPtr& par = mParamsPtr.back();
	par.name = name;
	initHandle(par);
	par.size = size;
	par.ptr = ptr;
}

void CEffectParams::addProxy(TParamName name, const CBaseProxyClass& proxy)
{
	mParamsProxy.push_back(SParam1());
	SParam1& par = mParamsProxy.back();
	par.name = name;
	initHandle(par);
	par.proxy = &proxy;
}

void CEffectParams::removeParam1(TParamName name)
{
	auto last = mParams1.end();
	for (auto first = mParams1.begin(); first != last; )
	{
		if (!strcmp(first->name.c_str(), name))
			first = mParams1.erase(first), last = mParams1.end();
		else
			++first;
	}
}

void CEffectParams::removeParam3(TParamName name)
{
	auto last = mParams3.end();
	for (auto first = mParams3.begin(); first != last; )
	{
		if (!strcmp(first->name.c_str(), name))
			first = mParams3.erase(first), last = mParams3.end();
		else
			++first;
	}
}

void CEffectParams::removeParam4(TParamName name)
{
	auto last = mParams4.end();
	for (auto first = mParams4.begin(); first != last; )
	{
		if (!strcmp(first->name.c_str(), name))
			first = mParams4.erase(first), last = mParams4.end();
		else
			++first;
	}
}

void CEffectParams::removeParam16(TParamName name)
{
	auto last = mParams16.end();
	for (auto first = mParams16.begin(); first != last; )
	{
		if (!strcmp(first->name.c_str(), name))
			first = mParams16.erase(first), last = mParams16.end();
		else
			++first;
	}
}

void CEffectParams::removeParamPtr(TParamName name)
{
	auto last = mParamsPtr.end();
	for (auto first = mParamsPtr.begin(); first != last; )
	{
		if (!strcmp(first->name.c_str(), name))
			first = mParamsPtr.erase(first), last = mParamsPtr.end();
		else
			++first;
	}
}

void CEffectParams::removeParamProxy(TParamName name)
{
	auto last = mParamsProxy.end();
	for (auto first = mParamsProxy.begin(); first != last; )
	{
		SParam1& p = *first;
		if (!strcmp(p.name.c_str(), name))
		{
			// unset from effect, otherwise we can leak
			if (p.handle)
			{
				assert(mEffect);
				ID3DXEffect* fx = mEffect->getObject();
				assert(fx);

				const void* ptr = NULL;
				fx->SetValue(p.handle, &ptr, sizeof(ptr));
			}

			first = mParamsProxy.erase(first), last = mParamsProxy.end();
		}
		else
		{
			++first;
		}
	}
}

void CEffectParams::clear()
{
	mParams1.clear();
	mParams3.clear();
	mParams4.clear();
	mParams16.clear();
	mParamsPtr.clear();
	mParamsProxy.clear();
}

void CEffectParams::setEffect(CD3DXEffect& fx, bool force)
{
	if (!force && mEffect && (fx.getObject() == mEffect->getObject()))
		return;

	mEffect = &fx;
	if (!mEffect)
		return;

	assert(mEffect && mEffect->getObject());

	// recalculate parameter handles
	for (auto it1 = mParams1.begin(); it1 != mParams1.end(); ++it1)
	{
		initHandle(*it1);
	}
	for (auto it3 = mParams3.begin(); it3 != mParams3.end(); ++it3)
	{
		initHandle(*it3);
	}
	for (auto it4 = mParams4.begin(); it4 != mParams4.end(); ++it4)
	{
		initHandle(*it4);
	}
	for (auto it16 = mParams16.begin(); it16 != mParams16.end(); ++it16)
	{
		initHandle(*it16);
	}
	for (auto itPtr = mParamsPtr.begin(); itPtr != mParamsPtr.end(); ++itPtr)
	{
		initHandle(*itPtr);
	}
	for (auto itProxy = mParamsProxy.begin(); itProxy != mParamsProxy.end(); ++itProxy)
	{
		initHandle(*itProxy);
	}
}

void CEffectParams::applyToEffect()
{
	assert(mEffect);
	ID3DXEffect* fx = mEffect->getObject();
	assert(fx);

	for (auto it1 = mParams1.begin(); it1 != mParams1.end(); ++it1)
	{
		SParam1& p = *it1;
		if (!p.handle) continue;
		fx->SetValue(p.handle, &p.valI, sizeof(p.valI));
	}
	for (auto it3 = mParams3.begin(); it3 != mParams3.end(); ++it3)
	{
		SParam3& p = *it3;
		if (!p.handle) continue;
		fx->SetValue(p.handle, &p.valV, sizeof(p.valV));
	}
	for (auto it4 = mParams4.begin(); it4 != mParams4.end(); ++it4)
	{
		SParam4& p = *it4;
		if (!p.handle) continue;
		fx->SetValue(p.handle, &p.valV, sizeof(p.valV));
	}
	for (auto it16 = mParams16.begin(); it16 != mParams16.end(); ++it16)
	{
		SParam16& p = *it16;
		if (!p.handle) continue;
		fx->SetValue(p.handle, &p.valM, sizeof(p.valM));
	}
	for (auto itPtr = mParamsPtr.begin(); itPtr != mParamsPtr.end(); ++itPtr)
	{
		SParamPtr& p = *itPtr;
		if (!p.handle) continue;
		fx->SetValue(p.handle, p.ptr, p.size);
	}
	for (auto itProxy = mParamsProxy.begin(); itProxy != mParamsProxy.end(); ++itProxy)
	{
		SParam1& p = *itProxy;
		if (!p.handle) continue;
		const void* ptr = p.proxy->getPtr();
		fx->SetValue(p.handle, &ptr, sizeof(ptr));
	}
}

#include "dingus/input/InputEvent.hpp"

using namespace dingus;


//---------------------------------------------------------------------------
// CInputEvent
//---------------------------------------------------------------------------
int CInputEvent::unique(const CInputEvent &e)
{
	return e.getType();
}

bool CInputEvent::operator<(const CInputEvent &rhs) const
{
	return (unique(*this) < unique(rhs));
}

//---------------------------------------------------------------------------
// CKeyEvent
//---------------------------------------------------------------------------
CKeyEvent::CKeyEvent(eMode mode, int ascii, int keyCode) :
	CInputEvent(EVENT_TYPE), mode_(mode), ascii_(ascii), keyCode_(keyCode)
{
}

int CKeyEvent::unique(const CKeyEvent &e, bool withSpecialKey)
{
	return (e.getMode() << 30) + (e.getAscii() << 16) + (withSpecialKey ? e.getKeyCode() : 0);
}

bool CKeyEvent::operator< (const CInputEvent &rhs) const
{
	if (CInputEvent::operator<(rhs))
		return true;

	if (getType() != rhs.getType())
		return false;

	const CKeyEvent &k = (const CKeyEvent&)rhs;
	if (!keyCode_ || !k.keyCode_)
		return unique(*this, false) < unique(k, false);
	else
		return unique(*this, true) < unique(k, true);
}

//---------------------------------------------------------------------------
// CMouseEvent
//---------------------------------------------------------------------------
int CMouseEvent::unique(const CMouseEvent &e)
{
	return (e.getMode() << 20) + (e.getButton() << 16) + (e.getClickCount());
}

bool CMouseEvent::operator< (const CInputEvent &rhs) const
{
	if (CInputEvent::operator<(rhs))
		return true;

	if (getType() != rhs.getType())
		return false;

	return (unique(*this) < unique((const CMouseEvent&)rhs));
}

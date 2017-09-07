#pragma once

#include "dingus/GlobalSetting.hpp"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace dingus {

// --------------------------------------------------------------------------

class CInputEvent : public CRefCounted
{
public:
	enum { EVENT_TYPE = 0 };
	typedef DingusSmartPtr<CInputEvent> TSharedPtr;

public:
	virtual ~CInputEvent() {}

	virtual bool operator<(const CInputEvent &rhs) const;
	int getType() const { return type_; }

protected:
	CInputEvent(int type) : type_(type) {}

	static int unique(const CInputEvent &e);

private:
	int type_;
};

// --------------------------------------------------------------------------

class CKeyEvent : public CInputEvent
{
public:
	enum { EVENT_TYPE = 1 };
	enum eMode { KEY_PRESSED, KEY_DOWN, KEY_RELEASED };

public:
	CKeyEvent(eMode mode, int ascii, int keyCode = 0);

	virtual bool operator<(const CInputEvent &rhs) const;

	eMode getMode() const { return mode_; }
	int getAscii() const { return ascii_; }
	int getKeyCode() const { return keyCode_; }

protected:
	static int unique(const CKeyEvent& e, bool withSpecialKey);

private:
	eMode mode_;
	int ascii_;
	int keyCode_;
};

// --------------------------------------------------------------------------

class CMouseEvent : public CInputEvent
{
public:
	enum { EVENT_TYPE = 2 };
	enum eMode { MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_DRAGGED, MOUSE_DOWN, MOUSE_MOVE, MOUSE_NO_ACTION };
	enum eMouseButton { NONE = 0, LEFT_BTN = 1, RIGHT_BTN = 2, MIDDLE_BTN = 4 };

public:
	CMouseEvent(eMode mode, eMouseButton button)
		: CInputEvent(EVENT_TYPE), mode_(mode), button_(button), x_(0), y_(0), clickCount_(1) {}
	CMouseEvent(eMode mode, eMouseButton button, int x, int y, int clickCount = 1)
		: CInputEvent(EVENT_TYPE), mode_(mode), button_(button), x_(x), y_(y), clickCount_(clickCount) {}

	virtual bool operator< (const CInputEvent &rhs) const;

	eMode getMode() const { return mode_; }
	eMouseButton getButton() const { return button_; }
	int getX() const { return x_; }
	int getY() const { return y_; }
	int getClickCount() const { return clickCount_; }

public:
	static int unique(const CMouseEvent &e);

private:
	eMode mode_;
	eMouseButton button_;
	int x_;
	int y_;
	int clickCount_;
};

// --------------------------------------------------------------------------

class CInputEvents
{
public:
	typedef std::vector<CInputEvent::TSharedPtr> TEventsVector;

public:
	CInputEvents() {}
	CInputEvents(const CInputEvents &events) : events_(events.events_) {}

	void addEvent(CInputEvent *e) { events_.push_back(e); }
	const TEventsVector& getEvents() const { return events_; }
	void clear() { events_.clear(); }

private:
	TEventsVector events_;
};

}
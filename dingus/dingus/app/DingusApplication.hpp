#pragma once

#include "dingus/GlobalSetting.hpp"
#include "dingus/console/Console.hpp"
#include "dingus/kernel/D3DDeviceCaps.hpp"

namespace dingus {

// --------------------------------------------------------------------------

struct SAppStartupParams
{
	
	const char* windowTitle;
	const char* dataPath;
	int windowWdith;
	int windowHeight;
	int minColorBits;
	int minAlphaBits;
	int minZBits;
	int minStencilBits;
	bool usesZBuffer;
	bool startFullscreen;
	bool showCursorFullscreen;
	bool vsyncFullscreen;
	bool debugTimer;
	bool selectDeviceAtStartup;
};

// --------------------------------------------------------------------------

class CD3DEnumeration;
class CD3DSettings;
// struct SD3DSettingsPref;

class IDingusAppContext
{
public:
	virtual const CD3DEnumeration& getD3DEnumeration() const = 0;
	virtual const CD3DSettings& getD3DSettings() const = 0;
	virtual void applyD3DSettings(const CD3DSettings& s) = 0;
};

// --------------------------------------------------------------------------

class IDingusApplication
{
public:
	virtual ~IDingusApplication() {}

	virtual SAppStartupParams getStartupParams() = 0;
	virtual bool checkDevice(const CD3DDeviceCaps& caps, CD3DDeviceCaps::eVertexProcessing vproc, CD3DEnumErrors& errors) = 0;
	// virtual void initD3DSettingsPref(SD3DSettingsPref& pref) {}

	// virtual void initialize(IDingusAppContext& appContext) = 0;
	virtual void initialize() = 0;
	virtual void shutdown() = 0;

	// Constantly polled, if returns true - app ends.
	virtual bool shouldFinish() = 0;

	// Constantly polled, if returns true - show render stats.
	virtual bool shouldShowStats() = 0;

	// Called to execute all main loop pipeline. It's applications task
	// to process contexts in needed order, etc.
	virtual void perform() = 0;

	// console related stuff
	virtual IConsoleRenderingContext* createStdConsoleCtx(HWND hwnd) = 0;

	// setup stuff
	virtual void setupBundles(const std::string& dataPath) = 0;
	virtual void setupContexts(HWND hwnd) = 0;
	virtual void destroyContexts() = 0;
	virtual void destroyBundles() = 0;

	// True if the message was processed.
	virtual bool msgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { return false; }
};

}

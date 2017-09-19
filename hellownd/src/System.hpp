#pragma once

#include <dingus/app/DingusApplication.hpp>

using namespace dingus;

class CSystem : public IDingusApplication
{
	virtual SAppStartupParams getStartupParams() override;
	virtual IConsoleRenderingContext* createStdConsoleCtx(HWND hwnd) override;

	virtual void setupBundles(const std::string& dataPath) override;
	virtual void setupContexts(HWND hwnd) override;
	virtual void destroyContexts() override;
	virtual void destroyBundles() override;

protected:
	HWND mHWnd;
};

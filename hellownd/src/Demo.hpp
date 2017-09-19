#pragma once

#include "System.hpp"

class CDemo : public CSystem
{
public:
	CDemo();
	virtual ~CDemo();

	virtual bool checkDevice(const CD3DDeviceCaps& caps, CD3DDeviceCaps::eVertexProcessing vproc, CD3DEnumErrors& errors) override;
	virtual void initialize() override;
	virtual void shutdown() override;
	virtual bool shouldFinish() override;
	virtual bool shouldShowStats() override;
	virtual void perform() override;
	virtual bool msgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
};

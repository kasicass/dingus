#pragma once

#include "dingus/dxutils/D3DApplication.hpp"
#include "dingus/app/DingusApplication.hpp"

namespace dingus {

class IConsoleRenderingContext;

class CDingusSystem : public CD3DApplication
{
public:
	CDingusSystem(IDingusApplication& application);
	virtual ~CDingusSystem();

	virtual LRESULT msgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

protected:
	virtual HRESULT initialize() override;
	virtual HRESULT createDeviceObjects() override;
	virtual HRESULT activateDeviceObjects() override;
	virtual HRESULT passivateDeviceObjects() override;
	virtual HRESULT deleteDeviceObjects() override;
	virtual HRESULT performOneTime() override;
	virtual HRESULT shutdown() override;

	virtual bool checkDevice(const CD3DDeviceCaps& caps, CD3DDeviceCaps::eVertexProcessing vproc, CD3DEnumErrors& errors) override;

private:
	IDingusApplication*        mApplication;
	std::string                mDataPath;
	bool                       mAppInited;

	IConsoleRenderingContext*  mStdConsoleCtx;
};

}

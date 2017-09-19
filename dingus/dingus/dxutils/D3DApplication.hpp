#pragma once

#include "dingus/GlobalSetting.hpp"
#include "dingus/kernel/D3DDeviceCaps.hpp"

namespace dingus {

//---------------------------------------------------------------------------
// error codes

enum eAppErr {
	NODIRECT3D           = 0x82000001,
	NOCOMPATIBLEDEVICES  = 0x82000003,
	NONZEROREFCOUNT      = 0x8200000a,
	RESETFAILED          = 0x8200000c,
	NULLREFDEVICE        = 0x8200000d,
};

class CD3DApplication : public boost::noncopyable
{
public:
	CD3DApplication();
	virtual ~CD3DApplication();

protected:
	// internal variables fro the state of the ap
	bool mWindowed;
	bool mActive;
	bool mDeviceLost;
	bool mMinimized;
	bool mMaximized;
	bool mIgnoreSizeChange;
	bool mDeviceObjectsInited;
	bool mDeviceObjectsRestored;

	HRESULT initialize3DEnvironment();
	HRESULT reset3DEnvironment();
	void cleanup3DEnvironment();

protected:
	DWORD mCreationWidth;
	DWORD mCreationHeight;
	const char* mWindowTitle;

	D3DPRESENT_PARAMETERS mPresentParams;
	HINSTANCE             mHInstance;
	HWND                  mHWnd;
	IDirect3D9*           mD3D;
	IDirect3DDevice9*     mD3DDevice;
	D3DCAPS9              mD3DCaps;
	D3DSURFACE_DESC       mBackBuffer;
	DWORD                 mCreateFlags;
	DWORD                 mWindowStyle;

protected:
	virtual HRESULT initialize() = 0;
	virtual HRESULT createDeviceObjects() = 0;
	virtual HRESULT activateDeviceObjects() = 0;
	virtual HRESULT passivateDeviceObjects() = 0;
	virtual HRESULT deleteDeviceObjects() = 0;
	virtual HRESULT performOneTime() = 0;
	virtual HRESULT shutdown() = 0;

	virtual bool checkDevice(const CD3DDeviceCaps& caps, CD3DDeviceCaps::eVertexProcessing vproc, CD3DEnumErrors& errors) = 0;

public:
	virtual HRESULT create(HINSTANCE hInstance);
	virtual int run();
	virtual LRESULT msgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void pause(bool bPause);
	bool isActive() const { return mActive; }
	void close();
	void doClose();

private:
	HRESULT	internalCreateDevice();
	HRESULT	internalDeleteDevice();
	HRESULT internalActivateDevice();
	HRESULT internalPassivateDevice();
};

}

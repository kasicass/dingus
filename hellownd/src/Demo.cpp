#include "Demo.hpp"
#include <dingus/kernel/D3DDevice.hpp>
#include <initguid.h>

CDemo::CDemo()
{
}

CDemo::~CDemo()
{
}

bool CDemo::checkDevice(const CD3DDeviceCaps& caps, CD3DDeviceCaps::eVertexProcessing vproc, CD3DEnumErrors& errors)
{
	return true;
}

void CDemo::initialize()
{
}

void CDemo::shutdown()
{
}

bool CDemo::shouldFinish()
{
	return false;
}

bool CDemo::shouldShowStats()
{
	return false;
}

void CDemo::perform()
{
	CD3DDevice& dx = CD3DDevice::getInstance();
	dx.clearTargets(true, true, true, D3DCOLOR_ARGB(0xff, 0xff, 0, 0));
}

bool CDemo::msgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return false;
}
